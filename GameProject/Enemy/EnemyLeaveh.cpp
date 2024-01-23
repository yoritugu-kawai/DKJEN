#include "EnemyLeaveh.h"

void EnemyStateLeave::Update(Enemy* enemy)
{

	
		/*pos_.translate.x += 0.1f;
		pos_.translate.y += 0.1f;
		
	if (pos_.translate.z <= -10) {
		pos_.translate.z = 10.0f;
		pos_.translate.x = 0.0f;
		pos_.translate.y = 0.0f;

	}*/
		enemy->SetPos(Add(enemy->GetPos().translate, versti));
		if (enemy->GetPos().translate.z < -50)
		{
			enemy->StateChange(new EnemyStateApproach);
			pos_.translate.z = 50.0f;
			pos_.translate.x = 0.0f;
			pos_.translate.y = 0.0f;
			enemy->SetPos(pos_.translate);
		}
}
