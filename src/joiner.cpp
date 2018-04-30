#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	tempTrackStyle = configuration.getConfigurations()["TrackGenerationStyle"];

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
	ImGui::InputInt("Track Style", &tempTrackStyle);
	if (tempTrackStyle < 0) { tempTrackStyle = 0; }
	if (tempTrackStyle > 1) { tempTrackStyle = 1; }

	if (ImGui::Button("Re-Initialize")) {
		configuration.setConfiguration("TrackGenerationStyle", tempTrackStyle);

		board = Board();
		world = World();
		initializeWorld();
	}
	ImGui::End();
}

void Joiner::draw() {
	glPushMatrix();
	glTranslatef(-camera.getPosition().x + (configuration.getScreenWidth() / 2) - (board.bitmapPolygon.getWidth() / 2), -camera.getPosition().y + (configuration.getScreenHeight() / 2) - (board.bitmapPolygon.getHeight() / 2), 0);
	world.draw();
	board.draw();
	glPopMatrix();

	hud.draw();
}