#include <stdio.h>
#include <stdint.h>
// #include <unistd.h>
#include <time.h>

#define BOARD_LENGTH 66
#define BOARD_WIDTH  269

#define BOARD_SIZE (BOARD_LENGTH * BOARD_WIDTH)

typedef struct {
    uint16_t board_index;
    uint16_t board[BOARD_SIZE];
} Board;

void display(Board* board) {
    // for (int i = 0; i < BOARD_WIDTH; i++)
    // {
    //     printf("- ");
    // }
    // printf("\n");
    printf("\033[2J");
    printf("\033[H"); 
    for (uint16_t i = board->board_index; i < BOARD_SIZE + board->board_index; i++)
    {
        if (board->board[i % (BOARD_SIZE)] == 1) {
            // printf("%d", board->board[i % (BOARD_SIZE) ]);
            printf("█");
        } else {
            printf(" ");
        }
        if ((i + 1) % BOARD_WIDTH == 0)
        {
            printf("\n");
        }
        
    }
    fflush(stdout);
    // for (int i = 0; i < BOARD_WIDTH; i++)
    // {
    //     printf("- ");
    // }
    // printf("\n");

}

void init(Board* board)
{

    board->board[0] = 1;
    board->board[56] = 1;
    board->board[33] = 1;
    board->board[20] = 1;

}

void update(Board* board)
{
    uint16_t it_past = board->board_index % (BOARD_SIZE);
    board->board_index = (board->board_index + (BOARD_SIZE) - BOARD_WIDTH) % (BOARD_SIZE);
    uint16_t it_future = board->board_index % (BOARD_SIZE);

    for (uint16_t i = 0; i < BOARD_WIDTH; i++)
    {
        if (i == 0) {
            //check the past: above and to the right
            uint16_t above = board->board[it_past + i];
            uint16_t right = board->board[(it_past + i + 1) % BOARD_SIZE];
            if (above + right == 1) {
                board->board[it_future + i] = 1;
            } else {
                board->board[it_future + i] = 0;
            }
        } else if (i == BOARD_WIDTH - 1) {
            //check the past: above and to the left
            uint16_t above = board->board[it_past + i];
            uint16_t left = board->board[(it_past + i - 1) % BOARD_SIZE];

            if (above + left == 1) {
                board->board[it_future + i] = 1;
            } else {
                board->board[it_future + i] = 0;
            }

        } else {
            //check the past: above and to the left and to the right
            uint16_t above = board->board[it_past + i];
            uint16_t left = board->board[(it_past + i - 1) % BOARD_SIZE];
            uint16_t right = board->board[(it_past + i + 1) % BOARD_SIZE];

            if (above + left + right == 1) {
                board->board[it_future + i] = 1;
            } else {
                board->board[it_future + i] = 0;
            }
        }

        // board->board[it_future + i] = board->board[it_past + i] + 1;
    }

}


int main(void)
{
    Board board = {0};

    init(&board);

    display(&board);

    struct timespec req;

    req.tv_sec = 0;
    req.tv_nsec = 250000000L;
    req.tv_nsec = 125000000L;

    for (;;)
    {
        update(&board);
        nanosleep(&req, NULL);
        display(&board);
    }



    return 0;
}