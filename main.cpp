#include <Novice.h>
#include "source/include.h"

const char kWindowTitle[] = "LC1A_27_ヤマグチ_タクト_タイトル";

struct Line {
	Vector2 start;
	Vector2 end;
};

struct Box {
	Vector2 pos;
	Vector2 screenPos;
	Vector2 size;
	Vector2 velo;
	Vector2 accel;
	float mass;
	unsigned int color;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	float theta = 0;
	Vector2 origineScale = { 1,1 };
	Vector2 originePos = { 0,0 };

	Vector2 cameraPos = { 500,200 };
	Vector2 cameraVelocity = { 0,0 };
	Vector2 cameraTransVelo = { 0,0 };
	Vector2 cameraDir = { 0,0 };
	Vector2 cameraScale = { 1,1 };

	Matrix3x3 origineWorldMatrix = MakeAffineMatrix(origineScale, theta, originePos);

	float cameraTheta = 0;
	Matrix3x3 cameraWorldMatrix = MakeAffineMatrix(cameraScale, cameraTheta, cameraPos);
	Matrix3x3 viewMatrix = Inverse(cameraWorldMatrix);
	Matrix3x3 orthoMatrix = MakeOrthographicMatrix(-640, 360, 640, -360);
	Matrix3x3 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720);
	Matrix3x3 origineWvpVpMatrix = Multiply(origineWorldMatrix, viewMatrix);
	origineWvpVpMatrix = Multiply(origineWvpVpMatrix, orthoMatrix);
	origineWvpVpMatrix = Multiply(origineWvpVpMatrix, viewportMatrix);


	Line line[82];
	for (int i = 0; i < 41; i++) {
		line[i].start = { -2000, 2000 - float(i * 100) };
		line[i].end = { 2000, 2000 - float(i * 100) };
		line[i + 41].start = { 2000 - float(i * 100), 2000 };
		line[i + 41].end = { 2000 - float(i * 100), -2000 };
	}

	Line screenLine[82];
	for (int i = 0; i < 82; i++) {
		screenLine[i].start = line[i].start;
		screenLine[i].end = line[i].end;
	}


	Box box = {
		{50,50},
		{0,0},
		{100,100},
		{0,0},
		{0,0},
		1.0f,
		0xFFFFFFFF
	};


	Vector2 kGravity = { 0,-9.8f };
	Vector2 len = (kGravity * -box.mass);
	float miu = 0.4f;
	float magnitude = miu * len.Length();

	Vector2 directoin;

	Vector2 frictionalForce = directoin * magnitude;




	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		origineWvpVpMatrix = Multiply(origineWorldMatrix, viewMatrix);
		origineWvpVpMatrix = Multiply(origineWvpVpMatrix, orthoMatrix);
		origineWvpVpMatrix = Multiply(origineWvpVpMatrix, viewportMatrix);


		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			box.velo.x = 70;
		}
		directoin = box.velo.Normalize();
		directoin.x = directoin.x * -1;
		frictionalForce = directoin * magnitude;

		if (fabsf(box.velo.x) > 0.01f) {
			box.accel = frictionalForce / box.mass;
		}

		if (fabs(box.accel.x / 60.0f) > fabs(box.velo.x)) {
			box.accel.x = box.velo.x * 60.0f;
		}

		box.velo += (box.accel / 60.0f);

		box.pos += (box.velo / 60.0f);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i < 82; i++) {
			screenLine[i].start = Transform(line[i].start, origineWvpVpMatrix);
			screenLine[i].end = Transform(line[i].end, origineWvpVpMatrix);
			if (i != 20 && i != 61) {
				Novice::DrawLine(int(screenLine[i].start.x), int(screenLine[i].start.y), int(screenLine[i].end.x), int(screenLine[i].end.y), BLACK);
			}
			else if (i == 20) {
				Novice::DrawLine(int(screenLine[i].start.x), int(screenLine[i].start.y), int(screenLine[i].end.x), int(screenLine[i].end.y), RED);
			}
			else {
				Novice::DrawLine(int(screenLine[i].start.x), int(screenLine[i].start.y), int(screenLine[i].end.x), int(screenLine[i].end.y), GREEN);
			}
		}
		box.screenPos = Transform(box.pos, origineWvpVpMatrix);
		Novice::DrawBox(int(box.screenPos.x - box.size.x / 2), int(box.screenPos.y - box.size.y / 2), int(box.size.x), int(box.size.y), 0.0f, box.color, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
