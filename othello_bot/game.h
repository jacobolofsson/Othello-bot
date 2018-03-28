#ifndef GAME_H
#define GAME_H

static const int GAME_COLUMNS = 8;
static const int GAME_ROWS = 8;

enum game_color {
    WHITE, 
    BLACK, 
    EMPTY
};
struct game_state {
    enum game_color positions[GAME_COLUMNS][GAME_ROWS];
};
struct game_move {
    int x_pos;
    int y_pos;
    enum game_color player;
};

extern void game_get_legal_moves(struct game_move *move_buffer, struct game_state state, enum game_color player);
extern void game_apply_move(struct game_state *state, struct game_move m);
extern bool game_is_over(struct game_state state);
extern enum game_color game_change_color(enum game_color color);

#endif // GAME_H
