#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	trackGenerationStyle = configuration.getConfigurations()["TrackGenerationStyle"];

	deckID = configuration.getConfigurations()["DeckID"];
	wheelID = configuration.getConfigurations()["WheelID"];

	initializeWorld();
}

void Joiner::reset(bool crashed, bool crashedParticles = true) {
	if (crashed) {
		isCrashed = true;

		if (crashedParticles) {
			particleManager.generateCrashParticles(20, board.bitmapPolygon.getCenter());
		}
		else { stillShowBoard = true; }
	}
	else {
		stillShowBoard = false;
		isKeyStart = false;
		allowKeyStart = false;
		world.reset();
		board.reset();
		hud.resetSplitsDisplay();
		selectedRun = hud.splitsDisplay.splitList.size() - 1;
	}
}

void Joiner::resetFull() {
	selectedRun = 0; 
	leaderboardSelectedRun = 0;

	isKeyStart = false;
	board = Board();
	world = World();
	hud = HUD();
	initializeWorld();
	particleManager.clearAllParticles();

	isCrashed = false;
	allowRestartAfterCrash = false;
	isKeyStart = false;
	allowKeyStart = false;

	showBoardEdit = false;
	showTrackEdit = false;
}

void Joiner::initializeWorld() {
	board.initialize();
	camera.linkPosition(board.bitmapPolygon.getPositionAddress());
	
	world.generateWorld();

	if (configuration.getConfigurations()["DrawMinimap"] == 1) {
		hud.initializeMinimap(world.track.railList, Vector2(0, 0), Vector2(0, 0), configuration.getScreenWidth() / 5, configuration.getScreenHeight() / 3);
	}
	hud.initializeSplitsDisplay(checkpointCount, world.track.railList[0][0], world.track.railList[0][world.track.railList[0].size() - 1]);
}

void Joiner::update() {
	// if (input.checkKeyDown(SDLK_f)) { isPaused = true; }
	// else { isPaused = false; }

	if (allowKeyStart && input.getKeyListSize() > 0 && ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) == false) {
		isKeyStart = true;
	}

	if (!isKeyStart) {
		if (allowKeyStart) {
			if (input.getKeyListSize() > 0 && ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) == false) {
				isKeyStart = true;
				allowKeyStart = false;
			}
		}
		else {
			if (input.getKeyListSize() == 0) {
				allowKeyStart = true;
			}
		}
	}

	if (isCrashed) {
		if (allowRestartAfterCrash) {
			if (input.getKeyListSize() > 0) {
				isCrashed = false;
				allowRestartAfterCrash = false;
				reset(false);
			}
		}
		else {
			if (input.getKeyListSize() == 0) {
				allowRestartAfterCrash = true;
			}
		}
	}

	if (isPaused == false && isKeyStart == true) {
		if (!isCrashed) {
			board.update(speedZone, trackDirection);
		}

		particleManager.update();
		world.update();

		if (configuration.getConfigurations()["DrawMinimap"] == 1) {
			hud.updateMinimap(board.bitmapPolygon.getPosition(), board.bitmapPolygon.getAngle());
		}

		if (!isCrashed) {
			hud.updateSplitsDisplay(board.bitmapPolygon.getPosition());
		}

		for (Vector2 speed : world.track.speedZones) {
			if (board.bitmapPolygon.getPosition().x > world.track.railList[0][speed.x].x) {
				speedZone = speed.y;
			}
		}

		for (Vector2 direction : world.track.trackDirection) {
			if (board.bitmapPolygon.getPosition().x > direction.x) {
				trackDirection = direction.y;
			}
		}

		for (std::vector<Vector2> rail : world.track.railList) {
			for (int x = 0; x < rail.size(); x++) {
				if (board.bitmapPolygon.getPosition().x + 100 > rail[x].x && board.bitmapPolygon.getPosition().x < rail[x].x + 100) {
					hud.resetMinimap();
					
					if (board.handleCollision(rail[x], rail[x + 1]) && !isCrashed) {
						reset(true);
					}
				}
			}
		}

		for (GravelRectangle& gravelRectangle : world.environment.gravel.gravelRectangleList) {
			if (board.bitmapPolygon.getPosition().x + 100 > gravelRectangle.position.x && board.bitmapPolygon.getPosition().x < gravelRectangle.position.x + 100) {
				if (board.handleCollision(gravelRectangle.position, gravelRectangle.width, gravelRectangle.height)) {
					board.forceSlide();
				}
			}
		}

		for (Squirrel& squirrel : world.environment.squirrelList) {
			if (board.bitmapPolygon.getPosition().x + 100 > squirrel.polygon.getPosition().x && board.bitmapPolygon.getPosition().x < squirrel.polygon.getPosition().x + 100) {
				if (board.handleCollision(squirrel.polygon)) {
					if (!squirrel.getDead()) { board.subtractSpeedExternal(50); }

					squirrel.kill();
				}
			}
		}

		for (Car car : world.environment.carList) {
			if (board.bitmapPolygon.getPosition().x + 100 > car.polygon.getPosition().x && board.bitmapPolygon.getPosition().x < car.polygon.getPosition().x + 100) {
				if (board.handleCollision(car.polygon) && !isCrashed) {
					reset(true);
				}
			}

			//Frame Killer
			// for (Squirrel& squirrel : world.environment.squirrelList) {
			// 	if (car.handleCollision(squirrel.polygon)) {
			// 		squirrel.kill();
			// 	}
			// }
		}
		
		for (Bike& bike : world.environment.bikeList) {
			if (board.bitmapPolygon.getPosition().x + 100 > bike.polygon.getPosition().x && board.bitmapPolygon.getPosition().x < bike.polygon.getPosition().x + 100) {
				if (board.handleCollision(bike.polygon) && !isCrashed) {
					if (!bike.getDead()) { 
						if (board.getVelocity() < 200) { reset(true); }
						board.subtractSpeedExternal(100); 
					}
					

					bike.kill();
				}
			}
		}

		if (board.bitmapPolygon.getPosition().x > hud.splitsDisplay.checkpointList[hud.splitsDisplay.checkpointList.size() - 1]) {
			hud.updateSplitsDisplay(board.bitmapPolygon.getPosition());
			particleManager.generateFinishParticles(2, board.bitmapPolygon.getCenter());
			reset(true, false);
		}

		if (input.checkKeyDown(SDLK_r) && !isCrashed) {
			reset(true);
		}

	}

	ImGui::SetNextWindowSizeConstraints(ImVec2(230, 165), ImVec2(230, 165));
	ImGui::Begin("Main Menu");

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 90);
	if (ImGui::Button("Edit Track")) {
		showTrackEdit = !showTrackEdit;
	}
	ImGui::NextColumn();
	if (ImGui::Button("Edit Board")) {
		showBoardEdit = !showBoardEdit;
	}

	ImGui::Columns(1);

	if (ImGui::Button("Leaderboards")) {
		showLeaderboards = !showLeaderboards;
	}
	
	if (ImGui::Button("Apply Changes / Re-Initialize")) {
		configuration.setConfiguration("TrackGenerationStyle", trackGenerationStyle);
		configuration.setConfiguration("DeckID", deckID);
		configuration.setConfiguration("WheelID", wheelID);

		if (randomTrackSeed == true) {
			joiner.seed = time(NULL);
		}

		srand(seed);
		resetFull();
	}

	ImGui::Checkbox("Display Session Stats", &showSessionStats);
	ImGui::Checkbox("Display Wheel Stats", &showWheelStats);
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	ImGui::End();

	if (showLeaderboards) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(225, 350), ImVec2(225, 350));
		ImGui::Begin("Leaderboards");

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 115);
		if (ImGui::Button("Export Splits")) {
			file.exportSplits(seed, hud.splitsDisplay.splitList[leaderboardSelectedRun], hud.splitsDisplay.finalTimeList[leaderboardSelectedRun]);
		}
		ImGui::InputInt("Run #", &leaderboardSelectedRun);
		if (leaderboardSelectedRun < 0) {
			leaderboardSelectedRun = 0;
		}
		if (leaderboardSelectedRun > hud.splitsDisplay.splitList.size() - 1) {
			leaderboardSelectedRun = hud.splitsDisplay.splitList.size() - 1;
		}
		ImGui::NextColumn();
		ImGui::SetColumnWidth(1, 150);
		if (ImGui::Button("Remove Run")) {
			hud.splitsDisplay.removeRun(leaderboardSelectedRun);
		}
		if (ImGui::Button("Best Time")) {
			leaderboardSelectedRun = hud.splitsDisplay.getBestTimeIndex();
		}
		ImGui::Columns(1);

		if (ImGui::Button("Close")) {
			showLeaderboards = false;
		}

		ImGui::TextColored(ImVec4(1,0,0,1), "Final: %f", hud.splitsDisplay.finalTimeList[leaderboardSelectedRun]);
		ImGui::TextColored(ImVec4(1,1,0,1), "Splits");
		ImGui::BeginChild("Scrolling");
		for (int x = 0; x < hud.splitsDisplay.splitList[leaderboardSelectedRun].size(); x++) {
		    ImGui::Text("#%i : %f", x + 1, hud.splitsDisplay.splitList[leaderboardSelectedRun][x]);
		}
		ImGui::EndChild();
		ImGui::End();
	}

	if (showSessionStats) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(125, 250), ImVec2(125, 250));
		ImGui::Begin("Session Stats");
		if (selectedRun != hud.splitsDisplay.splitList.size() - 1) {
			selectedRun = hud.splitsDisplay.splitList.size() - 1;
		}
		ImGui::TextColored(ImVec4(0,1,1,1), "Current Run: %i", selectedRun);
		ImGui::TextColored(ImVec4(1,0,0,1), "Final: %f", hud.splitsDisplay.finalTimeList[selectedRun]);
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1,1,0,1), "Splits");
		ImGui::BeginChild("Scrolling", ImVec2(0,0), false, ImGuiWindowFlags_NoScrollbar);
		for (int x = 0; x < hud.splitsDisplay.splitList[selectedRun].size(); x++) {
		    ImGui::Text("#%i : %f", x + 1, hud.splitsDisplay.splitList[selectedRun][x]);
	   		ImGui::SetScrollHere(1);
		}
		ImGui::EndChild();
		ImGui::End();
	}

	if (showWheelStats) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(240, 105), ImVec2(240, 105));
		ImGui::Begin("Wheel Stats");
		ImGui::TextColored(ImVec4(0,1,0,1), "Traction Multiplier: x%.03f", (2.00 - board.wheel.getTraction()));
		ImGui::TextColored(ImVec4(1,0,1,1), "Speed Multiplier: x%.03f", board.wheel.getRollSpeed());
		ImGui::TextColored(ImVec4(0.59,0.75,1,1), "Thane Left Till Core: %.2f%%", board.wheel.getCurrentHeightPercent() * 100);
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.96,0.57,0.26,1), "Velocity: %.2f", board.getVelocity());
		ImGui::End();
	}

	if (showTrackEdit) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(200, 155), ImVec2(200, 155));
		ImGui::Begin("Edit Track");
		ImGui::PushItemWidth(-250);
		ImGui::InputInt("Style", &trackGenerationStyle);
		if (trackGenerationStyle < 0) { trackGenerationStyle = 0; }
		if (trackGenerationStyle > 2) { trackGenerationStyle = 2; }

		ImGui::TextColored(ImVec4(0,1,1,1), configuration.getNameConfigurations()[("TrackStyle" + std::to_string(trackGenerationStyle)).c_str()].c_str());

		ImGui::PushItemWidth((ImGui::GetWindowWidth() / 2) - 15);
		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();

		ImGui::Checkbox("Random Seed", &randomTrackSeed);
		ImGui::PushItemWidth(150);
		ImGui::InputInt("Seed", &seed);

		if (ImGui::Button("Close")) {
			showTrackEdit = false;
		}

		ImGui::End();
	}

	if (showBoardEdit) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(380, 245), ImVec2(380, 245));
		ImGui::Begin("Edit Board");
		ImGui::Columns(2);
		ImGui::PushItemWidth(-175);
		ImGui::SetColumnWidth(0, 200);
		ImGui::InputInt("Board Preset", &deckID);
		if (deckID < 1) { deckID = 1; }
		if (deckID > getDeckCount()) { deckID = getDeckCount(); }

		ImGui::TextColored(ImVec4(0,1,1,1), getDeck(deckID).getName().c_str());
		ImGui::TextColored(ImVec4(0.6,0.6,1,1), "Length: %i\"", getDeck(deckID).getLength());
		ImGui::TextColored(ImVec4(0.6,0.6,1,1), "Width: %i\"", getDeck(deckID).getWidth());
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.8,0.4,1,1), "Turn Radius: x%.03f", getDeck(deckID).getTurnRadius());

		ImGui::NextColumn();

		ImGui::PushItemWidth(-175);
		ImGui::InputInt("Wheel Preset", &wheelID);
		if (wheelID < 1) { wheelID = 1; }
		if (wheelID > getWheelCount()) { wheelID = getWheelCount(); }

		ImGui::TextColored(ImVec4(0,1,1,1), getWheel(wheelID).getName().c_str());
		ImGui::TextColored(ImVec4(0.6,0.6,1,1), "Height: %imm", (int)getWheel(wheelID).getHeight());
		ImGui::TextColored(ImVec4(0.6,0.6,1,1), "Width: %imm", (int)getWheel(wheelID).getWidth());
		ImGui::TextColored(ImVec4(0.8,0.4,1,1), "Duro: %ia", getWheel(wheelID).getDurometer());
		ImGui::TextColored(ImVec4(1,0.6,1,1), "Strength: %i", getWheel(wheelID).getStrength());
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.7,0.3,1,1), ("Lip Profile: " + getWheelLipProfile(getWheel(wheelID).getLipID())).c_str());
		ImGui::TextColored(ImVec4(0.7,0.3,1,1), ("Has Skin? " + getWheelHasSkin(getWheel(wheelID).getHasSkin())).c_str());
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0,1,0,1), "Base Traction: x%.03f", (2.00 - getWheel(wheelID).getTraction()));
		ImGui::TextColored(ImVec4(1,0,1,1), "Base Speed: x%.03f", getWheel(wheelID).getRollSpeed());
		ImGui::Columns(1);
		ImGui::Spacing();

		if (ImGui::Button("Close")) {
			showBoardEdit = false;
		}
		ImGui::End();
	}
}

void Joiner::draw() {
	glPushMatrix();
	glTranslatef(-camera.getPosition().x + (configuration.getScreenWidth() / 2) - (board.bitmapPolygon.getWidth() / 2), -camera.getPosition().y + (configuration.getScreenHeight() / 2) - (board.bitmapPolygon.getHeight() / 2), 0);
	world.draw();
	board.drawThaneLines();
	if (!isCrashed || stillShowBoard) { board.draw(); }
	particleManager.draw();
	glPopMatrix();

	hud.draw();
}