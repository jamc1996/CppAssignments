class Board
{
private:
  int nrows;
  int ncols;
  bool* red_spots;
  bool* yellow_spots;
  int* valids;
  bool** red_entry;
  bool** yellow_entry;
  bool red_win, yellow_win;


  // Constructor:
public:
  Board(const int n, const int m);

  void make_move(bool p, int i);

  void print();

};
