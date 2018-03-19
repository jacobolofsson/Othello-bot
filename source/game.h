#ifndef GAME_H
#define GAME_H

const COLUMNS = 8;
const ROWS = 8;

struct move {
    int x_pos;
    int y_pos;
    player_t color;
}

struct move get_legal_moves(board_t board, color_t player_color);

board_t apply_move(board_t board, position_t move);

bool is_game_over(board_t board);

#endif // GAME_H
