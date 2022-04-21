import sys


BINGO_BOARD_SIZE = 5


class Colours:
    GREEN = '\033[92m'
    RED = '\033[91m'
    END_COLOUR = '\033[0m'


class BingoBoardNumber:

    def __init__(self, number):
        self.number = number
        self.marked = False

    def check_number(self, number):
        if self.number == number:
            self.marked = True
            return True
        return False

    def __str__(self):
        colour = Colours.GREEN if self.marked else Colours.RED
        return colour + "{:2}".format(str(self.number)) + Colours.END_COLOUR

    def __repr__(self):
        return str(self)


class BingoBoard:

    def __init__(self, board):
        self.board = board
        self.has_bingo = False

    def _check_row_bingo(self, row_num):
        has_bingo = True
        for i in range(len(self.board)):
            board_num = self.board[row_num][i]
            has_bingo = has_bingo and board_num.marked
        return has_bingo

    def _check_col_bingo(self, col_num):
        has_bingo = True
        for i in range(len(self.board[col_num])):
            board_num = self.board[i][col_num]
            has_bingo = has_bingo and board_num.marked
        return has_bingo

    def check_bingo(self):
        if self.has_bingo:
            return False
        for i in range(len(self.board)):
            self.has_bingo = self._check_row_bingo(i)
            if self.has_bingo:
                return self.has_bingo
        for i in range(len(self.board)):
            self.has_bingo = self._check_col_bingo(i)
            if self.has_bingo:
                return self.has_bingo

        return self.has_bingo

    def cross_number(self, number):
        for row in self.board:
            for board_num in row:
                if board_num.check_number(number):
                    return self.check_bingo()
        return False

    def calc_score(self, number):
        unmarked_sum = 0
        for row in self.board:
            for col in row:
                unmarked_sum += 0 if col.marked else col.number
        return unmarked_sum * number

    def __str__(self):
        s = "\n"
        for row in self.board:
            s += str(row) + "\n"
        return s

    def __repr__(self):
        return str(self)

def solution1(input_file):

    nums = []
    boards = []

    with open(input_file, 'r') as f:
        nums = [int(num) for num in next(f).split(",")]

        for line in f:
            board = []
            for i in range(BINGO_BOARD_SIZE):
                board.append([BingoBoardNumber(int(num)) for num in next(f).split()])
            boards.append(BingoBoard(board))

    for num in nums:
        for board in boards:
            if board.cross_number(num):
                prev_bingo_board = board
                prev_score = board.calc_score(num)

    print(prev_score)
    print(prev_bingo_board)


if __name__ == "__main__":
    solution1(sys.argv[1])
