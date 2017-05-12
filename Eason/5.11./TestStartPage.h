#ifndef _TESTSTARTPAGE_H_
#define _TESTSTARTPAGE_H_

#include "cocos2d.h"
#include "CollisionList.h"
#include "character.h"
#include "Monster.h"
//#include "SceneManager.h"

class GameStartPage : public cocos2d::Layer
{
public:
	int monsterNum;
	int currentMonsterNum;
	//�ж���Ϸ����
	bool done;

	CollisonList cl;
	cocos2d::Point screenO;
	character maincharacter;
	//auto bg;
//	Sprite* sprite;
public:

	//��ʼ������
	void initMonster();
	//��ʼ������״̬
	void initMstatus(Monster* & m);

	//update �и��¹���״̬
	void updateMonster(float delta);
	//ÿһ�������ؿ�������һ����ײ�б�
	void initCL();
	
	//���¹�����ײ�б�
	void updateCL();
	//�����Һ�CL�е���ײ
	PandS checkCL(float x1, float y1, int w1, int h1);
	//���ֺ͹ֵ���ײ������������cheackCL
	PandS checkCL(float x1, float y1, int w1, int h1, std::string monsterName);
	//���ֺ�ǽ����ײ
	PandS checkWall(float x1, float y1, int w1, int h1);

	//����Ѳ��
	void monsterPatrol(float dt);
	//���﹥��
	void monsterAttack(float delta);
	/*void monsterPatrol2(float dt);
	void monsterPatrol3(float dt);
	void monsterPatrol4(float dt);*/

	//�ƶ���ͼԪ��
	void moveCL(float dx, float dy);

	//����Ѫ��
	void updateHP();

	//����ӵ�
	void checkBullet();

	//����������
	void createPortal(float dt);

	//��������
	void updateScore();
	int getScore(int number);

	//�����
	void dropSoul(Vec2 position);

	static cocos2d::Scene* createNewScene();

	virtual bool init() override;
	void menuItemCallback(Ref * pSender);

	//here is keyboard scene code from game from scratch.com
	virtual void update(float delta) override;

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);


	void keyEvent(float delta);

	void fire(float dt);

	int BulletNumber;

	int score;

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label * label;

	CREATE_FUNC(GameStartPage);
};
#endif // __GAMESTARTPAGE_H__
