#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	trackGenerationStyle = configuration.getConfigurations()["TrackGenerationStyle"];
	boardID = configuration.getConfigurations()["BoardID"];
	boardWidth = configuration.getConfigurations()["BoardWidth"];
	boardHeight = configuration.getConfigurations()["BoardHeight"];

	initializeWorld();
}

void Joiner::initializeWorld() {
	board.initialize();
	camera.linkPosition(board.bitmapPolygon.getPositionAddress());
	
	world.generateWorld();

	if (configuration.getConfigurations()["DrawMinimap"] == 1) {
		hud.initializeMinimap(world.track.railList, Vector2(0, 0), Vector2(5, 5), configuration.getScreenWidth() / 5, configuration.getScreenHeight() / 3);
	}
}

void Joiner::update(int elapsedTime) {
	board.update(elapsedTime, speedZone);
	if (configuration.getConfigurations()["DrawMinimap"] == 1) {
		hud.updateMinimap(board.bitmapPolygon.getPosition(), board.bitmapPolygon.getAngle());
	}

	for (Vector2 speed : world.track.speedZones) {
		if (board.bitmapPolygon.getPosition().x > world.track.railList[0][speed.x].x) {
			speedZone = speed.y;
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

	ImGui::SetNextWindowSizeConstraints(ImVec2(200, 200), ImVec2(200, 200));
	ImGui::Begin("Main Menu");

	ImGui::PushItemWidth(-100);
	ImGui::InputInt("Track Style", &trackGenerationStyle);
	if (trackGenerationStyle < 0) { trackGenerationStyle = 0; }
	if (trackGenerationStyle > 1) { trackGenerationStyle = 1; }

	if (ImGui::Button("Edit Board Properties")) {
		showBoardProperty = true;
	}

	if (ImGui::Button("Re-Initialize")) {
		configuration.setConfiguration("TrackGenerationStyle", trackGenerationStyle);
		configuration.setConfiguration("BoardID", boardID);
		configuration.setConfiguration("BoardWidth", boardWidth);
		configuration.setConfiguration("BoardHeight", boardHeight);

		board = Board();
		world = World();
		initializeWorld();
	}
	ImGui::End();

	if (showBoardProperty) {
		ImGui::SetNextWindowSizeConstraints(ImVec2(300, 200), ImVec2(300, 200));
		ImGui::Begin("Board Property");
		ImGui::PushItemWidth(-175);
		ImGui::InputInt("Board ID", &boardID);
		ImGui::Columns(2);
		ImGui::InputInt("Width", &boardWidth);
		ImGui::NextColumn();
		ImGui::InputInt("Height", &boardHeight);
		ImGui::Columns(1);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() - 100);
		ImGui::ColorEdit4("Board Color", boardColor);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() - 100);
		ImGui::ColorEdit3("Thane Color", thaneColor);
		if (ImGui::Button("Close")) {
			showBoardProperty = false;
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