import random

# Define the ranks and suits (suits are not needed for the game logic)
ranks = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
values = {'2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10, 'J': 11, 'Q': 12, 'K': 13, 'A': 14}

# Initialize deck (no suits needed for the logic)
deck = ranks * 4  # Multiply to simulate 4 suits for each rank

# Shuffle the deck
random.shuffle(deck)

def get_card():
    """Draw the top card from the deck."""
    return deck.pop() if deck else None

def higher_or_lower_game():
    score = 0
    current_card = get_card()  # Draw the first card
    print("Welcome to Higher or Lower!")
    
    while current_card:
        print(f"\nCurrent card: {current_card}")
        guess = input("Will the next card be higher or lower? (h/l): ").lower()
        
        next_card = get_card()  # Draw the next card
        if next_card is None:
            print("No more cards left. Game over!")
            break
        
        print(f"The next card is: {next_card}")
        
        # Compare the values
        current_value = values[current_card]
        next_value = values[next_card]
        
        # Check if the guess is correct
        if (guess == 'h' and next_value > current_value) or (guess == 'l' and next_value < current_value):
            print("Correct!")
            score += 1
            current_card = next_card  # Update current card for next round
        else:
            print("Incorrect!")
            print(f"Your final score is {score}.")
            break

# Start the game
higher_or_lower_game()
