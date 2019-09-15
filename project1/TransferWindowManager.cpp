#include "TransferWindowManager.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)
{
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager::SoccerTeam& team)
{
	os << team.fw << std::endl;
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}


TransferWindowManager::TransferWindowManager(std::string file_dir, int budget)
{
	m_budget = budget;

	std::ifstream in(file_dir);
	std::string line;

	vector <string> v; 

	while (std::getline(in, line))
	{
	//Fill in the code to initialize 4 Binary Search Trees(fw, mf, df, gk)
		char temp[line.size()];
		strcpy(temp, line.c_str());

		char *tok = strtok(temp, ",");

		while(tok!=NULL){
			v.push_back(tok);
			tok = strtok(NULL, ",");
		}
	}

	for(int i=0; i< v.size() ; i++){
		if(i%4 == 1){
			if(v[i] == " Forward"){
				//cout<<"1"<<endl;
				SoccerPlayerData data(v[i-1],v[i],std::stoi(v[i+1]),std::stoi(v[i+2]));
				fwBST.insert(data);
			}
			else if(v[i] == " Goalkeeper"){
				//cout<<"2"<<endl;
				SoccerPlayerData data(v[i-1],v[i], std::stoi(v[i+1]), std::stoi(v[i+2]));
				gkBST.insert(data);
			}
			else if(v[i] == " Midfielder"){
				//cout<<"3"<<endl;
				SoccerPlayerData data(v[i-1],v[i], std::stoi(v[i+1]), std::stoi(v[i+2]));
				mfBST.insert(data);
			}
			else{
				//cout<<"4"<<endl;
				SoccerPlayerData data(v[i-1],v[i], std::stoi(v[i+1]), std::stoi(v[i+2]));
				dfBST.insert(data);
			}
		}
	}

}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager)
{
	os << "********Forward List********" << std::endl;
	os << manager.fwBST;
	os << "****************************" << std::endl;

	os << "********Midflder List********" << std::endl;
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	os << "********Defender List********" << std::endl;
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	os << "********Goalkeeper List********" << std::endl;
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}

void TransferWindowManager::removePlayer(SoccerPlayerData data)
{
	if (data.m_position == "Forward")
		fwBST.deletion(data.m_ability);
	else if (data.m_position == "Midfielder")
		mfBST.deletion(data.m_ability);
	else if (data.m_position == "Defender")
		dfBST.deletion(data.m_ability);
	else //if (data.m_position == "Goalkeeper"
		gkBST.deletion(data.m_ability);
}

SoccerPlayerData TransferWindowManager::getBestPlayer(BinarySearchTree &tree, int budget){
	TreeNode *p = tree.m_root;

	while(p){
		if(p->m_data.m_transfer_fee < budget){
			if(p->m_right !=NULL)
				p = p->m_right;
			else 
				return p->m_data;
		}
		else if(p->m_data.m_transfer_fee > budget){
			if(p->m_left !=NULL){
				p = p->m_left;
			}
			else 
				return p->m_data;
		}
		else return p->m_data;
	}

	return p->m_data;
}

TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam()
{
	SoccerTeam best_team;
	
	//Fill in the code to search the best_team from 4 BSTs
	//The datas for best team must be stored in the variable best_team.
	//best team means the most powerful team that is defined in the project introduction file.
	TreeNode *gkNode = gkBST.m_root;

	int temp_budget[6];
	for(int i=0; i<6 ;i++){
		temp_budget[i] = m_budget-gkNode->m_data.m_transfer_fee;
	}
	int team_power[6];

	SoccerPlayerData bfw1 = getBestPlayer(fwBST, temp_budget[0]);
	temp_budget[0] = temp_budget[0] - bfw1.m_transfer_fee;
	SoccerPlayerData bmf1 = getBestPlayer(mfBST, temp_budget[0]);
	temp_budget[0] = temp_budget[0] - bmf1.m_transfer_fee;
	SoccerPlayerData bdf1 = getBestPlayer(dfBST, temp_budget[0]);
	temp_budget[0] = temp_budget[0] - bdf1.m_transfer_fee;
	team_power[0] = bfw1.m_ability + bmf1.m_ability + bdf1.m_ability;

	SoccerPlayerData bfw2 = getBestPlayer(fwBST, temp_budget[1]);
	temp_budget[1] = temp_budget[1] - bfw2.m_transfer_fee;
	SoccerPlayerData bdf2 = getBestPlayer(dfBST, temp_budget[1]);
	temp_budget[1] = temp_budget[1] - bdf2.m_transfer_fee;
	SoccerPlayerData bmf2 = getBestPlayer(mfBST, temp_budget[1]);
	temp_budget[1] = temp_budget[1] - bmf2.m_transfer_fee;
	team_power[1] = bfw2.m_ability + bmf2.m_ability + bdf2.m_ability;
//////////////////////////////////////////////////////////////////////////

	SoccerPlayerData bmf3 = getBestPlayer(mfBST, temp_budget[2]);
	temp_budget[2] = temp_budget[2] - bmf3.m_transfer_fee;
	SoccerPlayerData bfw3 = getBestPlayer(fwBST, temp_budget[2]);
	temp_budget[2] = temp_budget[2] - bfw3.m_transfer_fee;
	SoccerPlayerData bdf3 = getBestPlayer(dfBST, temp_budget[2]);
	temp_budget[2] = temp_budget[2] - bdf3.m_transfer_fee;
	team_power[2] = bfw3.m_ability + bmf3.m_ability + bdf3.m_ability;

	SoccerPlayerData bmf4 = getBestPlayer(mfBST, temp_budget[3]);
	temp_budget[3] = temp_budget[3] - bmf4.m_transfer_fee;
	SoccerPlayerData bdf4 = getBestPlayer(dfBST, temp_budget[3]);
	temp_budget[3] = temp_budget[3] - bdf4.m_transfer_fee;
	SoccerPlayerData bfw4 = getBestPlayer(fwBST, temp_budget[3]);
	temp_budget[3] = temp_budget[3] - bfw4.m_transfer_fee;
	team_power[3] = bfw4.m_ability + bmf4.m_ability + bdf4.m_ability;
//////////////////////////////////////////////////////////////////////////

	SoccerPlayerData bdf5 = getBestPlayer(dfBST, temp_budget[4]);
	temp_budget[4] = temp_budget[4] - bdf5.m_transfer_fee;
	SoccerPlayerData bfw5 = getBestPlayer(fwBST, temp_budget[4]);
	temp_budget[4] = temp_budget[4] - bfw5.m_transfer_fee;
	SoccerPlayerData bmf5 = getBestPlayer(mfBST, temp_budget[4]);
	temp_budget[4] = temp_budget[4] - bmf5.m_transfer_fee;
	team_power[4] = bfw5.m_ability + bmf5.m_ability + bdf5.m_ability;

	SoccerPlayerData bdf6 = getBestPlayer(dfBST, temp_budget[5]);
	temp_budget[5] = temp_budget[5] - bdf6.m_transfer_fee;
	SoccerPlayerData bmf6 = getBestPlayer(mfBST, temp_budget[5]);
	temp_budget[5] = temp_budget[5] - bmf6.m_transfer_fee;
	SoccerPlayerData bfw6 = getBestPlayer(fwBST, temp_budget[5]);
	temp_budget[5] = temp_budget[5] - bfw6.m_transfer_fee;
	team_power[5] = bfw6.m_ability + bmf6.m_ability + bdf6.m_ability;

	int maxpower=0;
	vector<int> num;
	for(int i=0; i<6; i++){
		if(maxpower <= team_power[i]){
			maxpower = team_power[i];
			num.push_back(i);
		}
	}

	best_team.gk = gkNode->m_data;

	if(num.size() == 1){
		if(num[0] == 0){
			best_team.fw = bfw1;
			best_team.mf = bmf1;
			best_team.df = bdf1;
			best_team.sum_transfer_fee = bfw1.m_transfer_fee + bmf1.m_transfer_fee + bdf1.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw1.m_ability + bmf1.m_ability + bdf1.m_ability + gkNode->m_data.m_ability;
		}
		else if(num[0] == 1){
			best_team.fw = bfw2;
			best_team.mf = bmf2;
			best_team.df = bdf2;
			best_team.sum_transfer_fee = bfw2.m_transfer_fee + bmf2.m_transfer_fee + bdf2.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw2.m_ability + bmf2.m_ability + bdf2.m_ability + gkNode->m_data.m_ability;
		}
		else if(num[0] == 2){
			best_team.fw = bfw3;
			best_team.mf = bmf3;
			best_team.df = bdf3;
			best_team.sum_transfer_fee = bfw3.m_transfer_fee + bmf3.m_transfer_fee + bdf3.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw3.m_ability + bmf3.m_ability + bdf3.m_ability + gkNode->m_data.m_ability;
		}
		else if(num[0] == 3){
			best_team.fw = bfw4;
			best_team.mf = bmf4;
			best_team.df = bdf4;
			best_team.sum_transfer_fee = bfw4.m_transfer_fee + bmf4.m_transfer_fee + bdf4.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw4.m_ability + bmf4.m_ability + bdf4.m_ability + gkNode->m_data.m_ability;
		}

		else if(num[0] == 4){
			best_team.fw = bfw5;
			best_team.mf = bmf5;
			best_team.df = bdf5;
			best_team.sum_transfer_fee = bfw5.m_transfer_fee + bmf5.m_transfer_fee + bdf5.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw5.m_ability + bmf5.m_ability + bdf5.m_ability + gkNode->m_data.m_ability;
		}
		else {
			best_team.fw = bfw6;
			best_team.mf = bmf6;
			best_team.df = bdf6;
			best_team.sum_transfer_fee = bfw6.m_transfer_fee + bmf6.m_transfer_fee + bdf6.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw6.m_ability + bmf6.m_ability + bdf6.m_ability + gkNode->m_data.m_ability;
		}

	}
	else {
		int min_left = temp_budget[num[0]];
		for(int i=0; i<num.size() ; i++){
			if(min_left > temp_budget[num[i]]){
				min_left = temp_budget[num[i]];
			}
		}

		int spot;
		for(spot=0; spot<6; spot++){
			if(min_left == temp_budget[spot])
				break;
		}

		if(spot == 0){
			best_team.fw = bfw1;
			best_team.mf = bmf1;
			best_team.df = bdf1;
			best_team.sum_transfer_fee = bfw1.m_transfer_fee + bmf1.m_transfer_fee + bdf1.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw1.m_ability + bmf1.m_ability + bdf1.m_ability + gkNode->m_data.m_ability;
		}
		else if(spot == 1){
			best_team.fw = bfw2;
			best_team.mf = bmf2;
			best_team.df = bdf2;
			best_team.sum_transfer_fee = bfw2.m_transfer_fee + bmf2.m_transfer_fee + bdf2.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw2.m_ability + bmf2.m_ability + bdf2.m_ability + gkNode->m_data.m_ability;
		}
		else if(spot == 2){
			best_team.fw = bfw3;
			best_team.mf = bmf3;
			best_team.df = bdf3;
			best_team.sum_transfer_fee = bfw3.m_transfer_fee + bmf3.m_transfer_fee + bdf3.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw3.m_ability + bmf3.m_ability + bdf3.m_ability + gkNode->m_data.m_ability;
		}
		else if(spot == 3){
			best_team.fw = bfw4;
			best_team.mf = bmf4;
			best_team.df = bdf4;
			best_team.sum_transfer_fee = bfw4.m_transfer_fee + bmf4.m_transfer_fee + bdf4.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw4.m_ability + bmf4.m_ability + bdf4.m_ability + gkNode->m_data.m_ability;
		}

		else if(spot == 4){
			best_team.fw = bfw5;
			best_team.mf = bmf5;
			best_team.df = bdf5;
			best_team.sum_transfer_fee = bfw5.m_transfer_fee + bmf5.m_transfer_fee + bdf5.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw5.m_ability + bmf5.m_ability + bdf5.m_ability + gkNode->m_data.m_ability;
		}
		else {
			best_team.fw = bfw6;
			best_team.mf = bmf6;
			best_team.df = bdf6;
			best_team.sum_transfer_fee = bfw6.m_transfer_fee + bmf6.m_transfer_fee + bdf6.m_transfer_fee + gkNode->m_data.m_transfer_fee;
			best_team.sum_ability = bfw6.m_ability + bmf6.m_ability + bdf6.m_ability + gkNode->m_data.m_ability;
		}
	}


	fwBST.deletion(best_team.fw.m_ability);
	mfBST.deletion(best_team.mf.m_ability);
	dfBST.deletion(best_team.df.m_ability);
	gkBST.deletion(best_team.gk.m_ability);

	return best_team;
}
