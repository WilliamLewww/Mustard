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

	configuration.setConfiguration("HardTrack", trackHard);

	initializeWorld();
}

void Joiner::initializeWorld() {
	board.initialize();
	camera.linkPosition(board.bitmapPolygon.getPositionAddress());
	
	world.generateWorld();

	if (configuration.getConfigurations()["DrawMinimap"] == 1) {
		hud.initializeMinimap(world.track.railList, Vector2(-1000, 0), Vector2(0, 0), configuration.getScreenWidth() / 5, configuration.getScreenHeight() / 3);
	}
}

void Joiner::update(int elapsedTime) {
	board.update(elapsedTime, speedZone, trackDirection);
	if (configuration.getConfigurations()["DrawMinimap"] == 1) {
		hud.updateMinimap(board.bitmapPolygon.getPosition(), board.bitmapPolygon.getAngle());
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
				world.reset();
				board.handleCollision(rail[x], rail[x + 1]);
				board.handleCollision(rail[x], rail[x + 1]);
			}
		}
	}

	ImGui::SetNextWindowSizeConstraints(ImVec2(225, 135), ImVec2(225, 135));
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

		configuration.setConfiguration("HardTrack", trackHard);

		board = Board();
		world = World();
		initializeWorld();

		showBoardEdit = false;
		showTrackEdit = false;
	}

	ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();

	if (ImGui::Button("Clear Thane")) {
		board.clearLines();
	}
	ImGui::Checkbox("Display Session Stats", &showSessionStats);
	ImGui::End();

	if (showSessionStats) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(150, 250), ImVec2(150, 250));
		ImGui::Begin("Session Stats");
		ImGui::End();
	}

	if (showTrackEdit) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(300, 195), ImVec2(300, 195));
		ImGui::Begin("Edit Track");
		ImGui::PushItemWidth(-100);
		ImGui::InputInt("Style", &trackGenerationStyle);
		if (trackGenerationStyle < 0) { trackGenerationStyle = 0; }
		if (trackGenerationStyle > 1) { trackGenerationStyle = 1; }


		ImGui::PushItemWidth((ImGui::GetWindowWidth() / 2) - 15);
		ImGui::InputInt("Difficulty", &trackDifficulty);

		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();
		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();

		ImGui::Checkbox("Hard Track", &trackHard);
		ImGui::Checkbox("Random Seed", &randomTrackSeed);
		ImGui::InputInt("Seed", &trackSeed);

		if (ImGui::Button("Close")) {
			showTrackEdit = false;
		}

		ImGui::End();
	}

	if (showBoardEdit) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(300, 160), ImVec2(300, 160));
		ImGui::Begin("Edit Board");
		ImGui::PushItemWidth(-175);
		ImGui::InputInt("Board ID", &boardID);
		ImGui::Columns(2);
		ImGui::PushItemWidth(-200);
		ImGui::Text(("Length: " + std::to_string(boardLength)).c_str());   
		ImGui::NextColumn();
		ImGui::PushItemWidth(-200);
		ImGui::Text(("Width: " + std::to_string(boardWidth)).c_str());   

		if (boardID < 1) { boardID = 1; }
		if (boardID > 5) { boardID = 5; }

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
			case 4:
				boardLength = configuration.getConfigurations()["PresetBoard4Length"];
				boardWidth = configuration.getConfigurations()["PresetBoard4Width"];
				break;
			case 5:
				boardLength = configuration.getConfigurations()["PresetBoard5Length"];
				boardWidth = configuration.getConfigurations()["PresetBoard5Width"];
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
	board.draw();
	glPopMatrix();

	hud.draw();
}