/**
	AUTHOR 		:	MAHARAJ TEERTHA DEB
	STOP_STALK 	:	stopstalk.com/user/profile/Teertha_Deb
	GitHub		:	github.com/TeerthaDeb
**/

#include <bits/stdc++.h>
#include <string>
using namespace std;

class player
{
private:
	char name[50];
	unsigned long long int score = 0;
	//friend bool compare_players(player , player); /* not gonna use it again */
public:
	player()
	{
	}
	~player()
	{
	}

	//setters:

	/**
	 * @brief Set the score object
	 * 
	 * @param player_score [long long int] : player Score
	 */
	void set_score(long long int player_score)
	{
		score = player_score;
	}

	/**
	 * @brief Set the name object
	 * 
	 * @param player_name [String] : Name of the player
	 */
	void set_name(string player_name)
	{
		strcpy(name , player_name.c_str());
	}

	//getters:

	/**
	 * @brief Get the name object
	 * 
	 * @return string name of the player
	 */
	string get_name()
	{
		return name;
	}

	/**
	 * @brief Get the score object
	 * 
	 * @return unsigned long long int current score of the player
	 */
	unsigned long long int get_score()
	{
		return score;
	}

	/**
	 * @brief Compares player using the score
	 * 
	 * @param b [Player] : Another Player
	 * @return true if calling player score is greater than the comparing player
	 * @return false otherwise
	 */
	bool is_greater(const player b)
	{
		return (this -> score > b.score);
	}
};