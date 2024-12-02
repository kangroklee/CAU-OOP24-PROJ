from cosine_simil import get_similar
from models import User

def generate_recs(user):
    if not isinstance(user, User):
        raise ValueError('Input only supports instance of User type.')

    # Get user watch history
    user_preference = {}
    print("DIAG - user.watched: ", user.watched)
    for film in user.watched:
        user_preference[film] = 1 # set multiplier to 1

    # Get user likes 
    print("DIAG - user.likes: ", user.likes)
    for film in user.likes:
        # prioritize 'liked but not yet watched' films (set multiplier to 3)
        # 'liked and watched' films (set multiplier to 2)
        user_preference[film] = user_preference.get(film, 2) + 1
    print("DIAG - user_preference: ", user_preference)

    # Get similar movies to what user liked/watched
    top_10_preferences = sorted(user_preference.items(), key=lambda item: item[1], reverse=True)[:10]
    print("DIAG - top_10_preferences: ", top_10_preferences)

    all_similar_movies = set()
    for film in top_10_preferences:
        similar_movies = get_similar(film[0]) # select title part from film tuple
        for index, row in similar_movies.iterrows():
            all_similar_movies.add((row['title'], row['vote_average'])) # add tuple
    print("DIAG - all_similar_movies: ", all_similar_movies)

    # Future feature: Get user's friends' watch history
    # Future feature: Get new releases (by using created_at field to identify newly added media)
    # Future feature: Get recommendations by favorite directors/actors (suggestion: inherit directors and actors from BasePerson class)
   
    # Remove watched movies (no need to do this)
    # Put liked but not yet watched films on top (no need to do this)

    # Sort by votes (input = max. 100, output: max. 15)
    top_voted = sorted(all_similar_movies, key=lambda item: item[1], reverse=True)[:15]

    # print("DIAG - result: ", top_voted)

    return top_voted