class Position {
public:
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }


    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    bool is_within_bounds() const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }
};
