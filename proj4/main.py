from models import User
from recs import generate_recs
from cosine_simil import title_to_index

'''
===sample code for testing===
'''

def main():
    alice = User("Alice") # 멜로 취향의 유저
    bob = User("Bob") # SF 취향의 유저

    alice_likes = ['The Great Gatsby', 'Little Women']
    alice_watched = ['Captain America', 'Pulp Fiction', 'Les Miserables']

    bob_likes = ['Inception', 'Star Wars']
    bob_watched = ['Captain America']

    alice_likes = list(map(title_to_index, alice_likes))
    alice_watched = list(map(title_to_index, alice_watched))
    bob_likes = list(map(title_to_index, bob_likes))
    bob_watched = list(map(title_to_index, bob_watched))

    print("alice_likes: ", alice_likes)
    print("alice_watched: ", alice_watched)

    for film in alice_likes:
        if film is not None:
            alice.add_like(film)
    for film in alice_watched:
        if film is not None:
            alice.add_watched(film)

    print("bob_likes: ", bob_likes)
    print("bob_watched: ", bob_watched)  
    for film in bob_likes:
        if film is not None:
            bob.add_like(film)
    for film in bob_watched:
        if film is not None:
            bob.add_watched(film)

    
    recs = generate_recs(alice)
    print("======RESULTS======")
    print("Recommendations for Alice: ")
    for i in recs:
        print(i[0])
    recs = generate_recs(bob)
    print("======RESULTS======")
    print("Recommendations for Bob: ")
    for i in recs:
            print(i[0])

if __name__ == "__main__":
    main()