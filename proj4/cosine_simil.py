import pandas as pd
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

data = pd.read_csv('./movies_metadata.csv', low_memory=False)
data = data.head(20000) # selects first N titles (out of approx. 45,000). may run out of memory if N is too big.

data['overview'] = data['overview'].fillna('')

tfidf = TfidfVectorizer(stop_words='english')
tfidf_matrix = tfidf.fit_transform(data['overview'])
print(tfidf_matrix.shape)

cosine_sim = cosine_similarity(tfidf_matrix, tfidf_matrix)

data = data.drop_duplicates(subset='title')
# indices = pd.Series(data.index, index=data['title']).drop_duplicates()
indices = pd.Series(data.index, index=data['title']).to_dict()
# indices = pd.Series(data.index, index=data['title'])

# print(indices['Jumanji'])

def get_similar(title, cosine_sim = cosine_sim):
    if isinstance(title, np.int64):
        idx = title
    elif isinstance(title, int):
        idx = title
    else:
        idx = indices[title] # get index of given title
    sim_scores = list(enumerate(cosine_sim[idx]))
    sim_scores = sorted(sim_scores, key=lambda x: x[1], reverse=True)

    sim_scores = sim_scores[1:11] # first index is itself; exclude that
    # print("TEST: ", sim_scores)

    movie_indices = [i[0] for i in sim_scores]
    # print("movie_indices: ", movie_indices)
    
    return data.loc[movie_indices, ['title', 'vote_average']] # returns DataFrame object

def title_to_index(title):
    try:
        return indices[title]
    except KeyError:
        return None