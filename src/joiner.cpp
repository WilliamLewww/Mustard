#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	trackGenerationStyle = configuration.getConfigurations()["TrackGenerationStyle"];
	boardID = configuration.getConfigurations()["BoardID"];
	boardLength = configuration.getConfigurations()["BoardLength"];
	boardWidth = configuration.getConfigurations()["BoardWidth"];

	boardColor[0] = (float)configuration.getConfigurations()["BoardColorR"] / 255;
	boardColor[1] = (float)configuration.getConfigurations()["BoardColorG"] / 255;
	boardColor[2] = (float)configuration.getConfigurations()["BoardColorB"] / 255;
	boardColor[3] = (float)configuration.getConfigurations()["BoardColorA"] / 255;

	thaneColor[0] = (float)configuration.getConfigurations()["ThaneColorR"] / 255;
	thaneColor[1] = (float)configuration.getConfigurations()["ThaneColorG"] / 255;
	thaneColor[2] = (float)configuration.getConfigurations()["ThaneColorB"] / 255;

	initializeWorld();
}

void Joiner::reset(bool crashed) {
	if (crashed) {
		isCrashed = true;
		particleManager.generateCrashParticles(20, board.bitmapPolygon.getCenter());
	}
	else {
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
	if (input.checkKeyDown(SDLK_f)) { isPaused = true; }
	else { isPaused = false; }

	if (allowKeyStart && input.getKeyListSize() > 0 && ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) == false) {
		isKeyStart = true;
	}

	if (!isKeyStart) {
		if (allowKeyStart) {
			if (input.getKeyListSize() > 0) {
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

		for (Squirrel& squirrel : world.environment.squirrelList) {
			if (board.handleCollision(squirrel.polygon)) {
				squirrel.kill();
			}
		}

		if (board.bitmapPolygon.getPosition().x > world.track.railList[0][world.track.railList[0].size() - 1].x) {
			reset(false);
		}

	}

	ImGui::SetNextWindowSizeConstraints(ImVec2(230, 155), ImVec2(230, 155));
	ImGui::Begin("Main Menu");

	ImGui::Columns(2);
	if (ImGui::Button("Edit Track")) {
		showTrackEdit = !showTrackEdit;
	}
	ImGui::NextColumn();
	if (ImGui::Button("Edit Board")) {
		showBoardEdit = !showBoardEdit;
	}

	ImGui::Columns(1);
	
	if (ImGui::Button("Apply Changes / Re-Initialize")) {
		configuration.setConfiguration("TrackGenerationStyle", trackGenerationStyle);
		configuration.setConfiguration("BoardID", boardID);
		configuration.setConfiguration("BoardLength", boardLength);
		configuration.setConfiguration("BoardWidth", boardWidth);

		configuration.setConfiguration("BoardColorR", boardColor[0] * 255);
		configuration.setConfiguration("BoardColorG", boardColor[1] * 255);
		configuration.setConfiguration("BoardColorB", boardColor[2] * 255);
		configuration.setConfiguration("BoardColorA", boardColor[3] * 255);

		configuration.setConfiguration("ThaneColorR", thaneColor[0] * 255);
		configuration.setConfiguration("ThaneColorG", thaneColor[1] * 255);
		configuration.setConfiguration("ThaneColorB", thaneColor[2] * 255);

		if (randomTrackSeed == true) {
			joiner.seed = time(NULL);
		}

		srand(seed);
		resetFull();
	}

	ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();

	ImGui::Columns(2);
	if (ImGui::Button("Clear Thane")) {
		board.clearLines();
	}
	ImGui::NextColumn();
	if (ImGui::Button("Leaderboards")) {
		showLeaderboards = !showLeaderboards;
	}
	ImGui::Columns(1);
	ImGui::Checkbox("Display Session Stats", &showSessionStats);
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
		ImGui::SetNextWindowSizeConstraints(ImVec2(150, 250), ImVec2(150, 250));
		ImGui::Begin("Session Stats");
		if (selectedRun != hud.splitsDisplay.splitList.size() - 1) {
			selectedRun = hud.splitsDisplay.splitList.size() - 1;
		}
		ImGui::TextColored(ImVec4(0,1,1,1), "Current Run: %i", selectedRun);
		ImGui::TextColored(ImVec4(1,0,0,1), "Final: %f", hud.splitsDisplay.finalTimeList[selectedRun]);
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1,1,0,1), "Splits");
		ImGui::BeginChild("Scrolling");
		for (int x = 0; x < hud.splitsDisplay.splitList[selectedRun].size(); x++) {
		    ImGui::Text("#%i : %f", x + 1, hud.splitsDisplay.splitList[selectedRun][x]);
		}
		ImGui::EndChild();
		ImGui::End();
	}

	if (showTrackEdit) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(300, 150), ImVec2(300, 150));
		ImGui::Begin("Edit Track");
		ImGui::PushItemWidth(-100);
		ImGui::InputInt("Style", &trackGenerationStyle);
		if (trackGenerationStyle < 0) { trackGenerationStyle = 0; }
		if (trackGenerationStyle > 2) { trackGenerationStyle = 2; }


		ImGui::PushItemWidth((ImGui::GetWindowWidth() / 2) - 15);

		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();
		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();

		ImGui::Checkbox("Random Seed", &randomTrackSeed);
		ImGui::InputInt("Seed", &seed);

		if (ImGui::Button("Close")) {
			showTrackEdit = false;
		}

		ImGui::End();
	}

	if (showBoardEdit) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(300, 155), ImVec2(300, 155));
		ImGui::Begin("Edit Board");
		ImGui::PushItemWidth(-175);
		ImGui::InputInt("Board Preset", &boardID);
		ImGui::Columns(2);
		ImGui::PushItemWidth(-200);
		ImGui::Text(("Length: " + std::to_string(boardLength)).c_str());   
		ImGui::NextColumn();
		ImGui::PushItemWidth(-200);
		ImGui::Text(("Width: " + std::to_string(boardWidth)).c_str());   

		if (boardID < 1) { boardID = 1; }
		if (boardID > 3) { boardID = 3; }

		switch (boardID) {
			case 1:
				boardLength = configuration.getConfigurations()["PresetBoard1Length"];
				boardWidth = configuration.getConfigurations()["PresetBoard1Width"];
				break;
			case 2:
				boardLength = configuration.getConfigurations()["PresetBoard2Length"];
				boardWidth = configuration.getConfigurations()["PresetBoard2Width"];
				break;
			case 3:
				boardLength = configuration.getConfigurations()["PresetBoard3Length"];
				boardWidth = configuration.getConfigurations()["PresetBoard3Width"];
				break;
		}

		ImGui::Columns(1);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() - 100);
		ImGui::ColorEdit4("Board Color", boardColor);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() - 100);
		ImGui::ColorEdit3("Thane Color", thaneColor);

		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();

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
	if (!isCrashed) { board.draw(); }
	particleManager.draw();
	glPopMatrix();

	hud.draw();
}