### Example run of change making in python

def change_making(coins, counts, n):
    #Make a matrix to be represent as a dynamic table to be fill up
    # 'Count' is list that store the amount of denominations at its corresponding
    # Index in the 'coins' list
    # Assuming coins is sorted from smallest to largest
    m = [[float('inf') for _ in range(n + 1)] for _ in range(len(coins) + 1)]
    for i in range(len(coins) + 1):
        m[i][0] = 0  # Zero amount can always be made with 0 coins

    # Store which coins are used at each step
    used_coins = [[[] for _ in range(n + 1)] for _ in range(len(coins) + 1)]

    for c in range(1, len(coins) + 1):
      coin = coins[c-1]
      for amount in range(1, n + 1):
        if coin <= amount:
          # Check if using one more coin of this type is within the remaining count
          if m[c][amount - coin] + 1 < m[c-1][amount] and used_coins[c][amount - coin].count(c-1) < counts[c-1] - used_coins[c-1][amount - coin].count(c-1):
            m[c][amount] = m[c][amount - coin] + 1
            used_coins[c][amount] = used_coins[c][amount - coin].copy()  # Copy, not append
            used_coins[c][amount].append(c-1)
          else:
            m[c][amount] = m[c-1][amount]
            used_coins[c][amount] = used_coins[c-1][amount][:]
        else:
          m[c][amount] = m[c-1][amount]
          used_coins[c][amount] = used_coins[c-1][amount][:]
    # Create a count of coins used based on the last filled 'used_coins' entry
    if m[len(coins)][n] == float('inf'):
        return -1, []  # No solution exists

    # Extract the count of each coin used from the last entry
    final_coins_used = [0] * len(coins)
    for index in used_coins[len(coins)][n]:
        final_coins_used[index] += 1

    coins_used = [(coins[i], final_coins_used[i]) for i in range(len(coins)) if final_coins_used[i] > 0]

    return m[len(coins)][n], coins_used

# Example usage
coins = [5, 10, 20, 50]
counts = [1, 26, 20, 6]  # Enough 20s to use
total_coins_used, coins_used_detail = change_making(coins, counts, 130)
print("Total coins used:", total_coins_used)
print("Detail of coins used:", coins_used_detail)
