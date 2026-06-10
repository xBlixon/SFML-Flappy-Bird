#include <string>

class GameResult {
private:
    int score;
    std::string dateTime;

public:
    GameResult(int score, std::string dateTime)
        : score(score), dateTime(std::move(dateTime)) {
    }

    int getScore() const {
        return score;
    }

    std::string getDateTime() const {
        return dateTime;
    }
};