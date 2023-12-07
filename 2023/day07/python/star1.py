import sys

from collections import defaultdict

def card_value(card):
    c = card
    if c == "T":
        c = 10
    elif c == "J":
        c = 11
    elif c == "Q":
        c = 12
    elif c == "K":
        c = 13
    elif c == "A":
        c = 14
    return int(c)

class Hand:

    def __init__(self, hand_str: str):
        self.str = hand_str
        self.card_counts = defaultdict(int)
        for c in hand_str:
            self.card_counts[c] += 1

    def compare(self, other):
        self_counts = sorted(self.card_counts.values())
        other_counts = sorted(other.card_counts.values())
        
        if len(self_counts) == 1 and len(other_counts) == 1:
            return self.second_compare(other)
        if self_counts[-1] != other_counts[-1]:
            return other_counts[-1] - self_counts[-1]

        if len(self_counts) == 2 and len(other_counts) == 2:
            return self.second_compare(other)
        if self_counts[-2] != other_counts[-2]:
            return other_counts[-2] - self_counts[-2]

        if len(self_counts) == 3 and len(other_counts) == 3:
            return self.second_compare(other)
        if self_counts[-3] != other_counts[-3]:
            return other_counts[-3] - self_counts[-3]

        if len(self_counts) == 4 and len(other_counts) == 4:
            return self.second_compare(other)
        if self_counts[-4] != other_counts[-4]:
            return other_counts[-4] - self_counts[-4]

        return self.second_compare(other)

    def second_compare(self, other):
        for i in range(len(self.str)):
            if card_value(self.str[i]) != card_value(other.str[i]):
                return card_value(other.str[i]) - card_value(self.str[i])
        return 0

    def __repr__(self):
        s = "".join(sorted(self.str))
        return f"{self.str} ({s})"

def solution(input_file):

    hands_bids = []
    winnings = 0

    with open(input_file, 'r') as f:
        for line in f:
            hand, bid = line.strip().split()
            hand = Hand(hand)
            bid = int(bid)

            if len(hands_bids) == 0:
                hands_bids.append((hand, bid))
                continue

            for i, hb in enumerate(hands_bids):
                if hand.compare(hb[0]) < 0:
                    hands_bids.insert(i, (hand, bid))
                    break
            else:
                hands_bids.append((hand, bid))
                pass
        
    for i, hb in enumerate(hands_bids):
        rank = len(hands_bids) - i
        winnings += hb[1] * rank

    return winnings


if __name__ == "__main__":
    print(f"The total winnings of all hands is {solution(sys.argv[1])}.")