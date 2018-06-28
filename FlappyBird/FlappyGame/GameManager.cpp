#include "GameManager.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

GameManager::GameManager() {

	mEngine = new Engine();
	mEngine->Initialize((char*)"Flappy Bird Game");

 	mBackgroundSprite_b = Sprite("Assets/Art/backgroundBack.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
 	mBackgroundSprite_m = Sprite("Assets/Art/backgroundMid.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
 	mBackgroundSprite_f = Sprite("Assets/Art/backgroundFront.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
	mBackgroundSprite_b.SetScale(0.5f);
	mBackgroundSprite_m.SetScale(0.5f);
	mBackgroundSprite_f.SetScale(0.5f);
 	background_back = Background(mBackgroundSprite_b, mBackgroundSprite_m);
	background_front = Background(mBackgroundSprite_f);

	Sprite testSprite = Sprite("Assets/Art/Bird.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
	testSprite.SetScale(0.15f);

	mFlapper = new Flapper(testSprite);
	mPipeManager = new PipeManager();

	mStartSprite = Sprite("Assets/Art/press_space_to_start.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
	mGameoverSprite = Sprite("Assets/Art/game-over.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
	mGameoverSprite.SetScale(0.2f);

	score_ones = Sprite("Assets/Art/Numbers/0.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
	score_ones.SetScale(3.0f);
	score_tens = Sprite("Assets/Art/Numbers/0.png", Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
	score_tens.SetScale(3.0f);

	mState = State::START;
}

GameManager::~GameManager() {
	delete mEngine;
	delete mFlapper;
	delete mPipeManager;
}

void GameManager::Start() {
	while (true)
	{
		mEngine->Update();
		
		switch (mState) {

		case State::START:
		{
			mEngine->BeginRender();
			background_back.Render();
			background_front.Render();
			mStartSprite.Render();
			mEngine->EndRender();

			if (Keyboard::KeyDown(GLFW_KEY_SPACE))
			{
				SetState(State::GAMEPLAY);
			}
			if (Keyboard::KeyDown(GLFW_KEY_ESCAPE))
			{
				exit(1);
			}
		}
		break;
		case State::GAMEPLAY:
		{
			background_back.Update();
			mPipeManager->Update();
			mFlapper->Update();
			background_front.SetSpeed(mPipeManager->GetPipeSpeed());
			background_front.Update();
			//update score Sprites:
			int player_points = mPipeManager->GetScore();
			UpdateScoreSprites(player_points);

			mEngine->BeginRender();
			background_back.Render();
			mFlapper->Render();
			mPipeManager->Render();
			background_front.Render();
			score_ones.Render();
			score_tens.Render();
			mEngine->EndRender();

			bool isDead = mPipeManager->CheckCollision(*mFlapper);
			if (mFlapper->GetSprite().GetPos()->y < 150 || mFlapper->GetSprite().GetPos()->y > Engine::SCREEN_HEIGHT) {
				isDead = true;
			}
			if (isDead)
			{
				SetState(State::GAMEOVER);
			}
		}
		break;
		case State::GAMEOVER:
		{
			mEngine->BeginRender();
			background_back.Render();
			mPipeManager->Render();
			mFlapper->Render();
			background_front.Render();
			score_ones.Render();
			score_tens.Render();
			mGameoverSprite.Render();
			mEngine->EndRender();

			if (Keyboard::KeyDown(GLFW_KEY_SPACE))
			{
				SetState(State::START);
			}
			if (Keyboard::KeyDown(GLFW_KEY_ESCAPE))
			{
				exit(1);
			}
		}
		break;
		default:
			cout << "Unhandled game state found: " << static_cast<int>(mState) << endl;
			break;
		}
	}
}

//Currently the game cannot handle 3 digit scores, however, it is fairly immpossible to score that high
void GameManager::UpdateScoreSprites(int currentScore) {
	stringstream spritePath_ones;
	stringstream spritePath_tens;
	int digitOffset = 0;
	int tensDigit = 0;
	if (currentScore >= 10)
	{
		digitOffset = 7;
		tensDigit = currentScore / 10;
		spritePath_ones << "Assets/Art/Numbers/" << currentScore % 10 << ".png";
		spritePath_tens << "Assets/Art/Numbers/" << tensDigit << ".png";
	}
	else {
		spritePath_ones << "Assets/Art/Numbers/" << currentScore << ".png";
		spritePath_tens << "Assets/Art/Numbers/" << currentScore << ".png";
	}


	string ones_path = spritePath_ones.str();
	string tens_path = spritePath_tens.str();

	score_ones = Sprite(ones_path, Vector3((float)Engine::SCREEN_WIDTH / 2 + digitOffset, (float)Engine::SCREEN_HEIGHT - (float)Engine::SCREEN_HEIGHT / 10, 0));
	score_ones.SetScale(2.0f);
	score_tens = Sprite(tens_path, Vector3((float)Engine::SCREEN_WIDTH / 2 - digitOffset, (float)Engine::SCREEN_HEIGHT - (float)Engine::SCREEN_HEIGHT / 10, 0));
	score_tens.SetScale(2.0f);

}

//private

void GameManager::SetState(State state) {
	mState = state;
	if (mState == State::START) {
		mFlapper->Reset();
		mPipeManager->Reset();
		background_back.Reset();
		background_front.Reset();
	}
}