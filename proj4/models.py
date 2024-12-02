import time

class BaseTimeEntity:
    created_at = time.time()

class User(BaseTimeEntity):
    def __init__(self, name):
        self.name = name
        self.likes = set()
        self.watched = set()

    def add_like(self, media):
        # if isinstance(media, Media):
        self.likes.add(media)

    def add_watched(self, media):
        # if isinstance(media, Media):
        self.watched.add(media)
    
class Media: 
    def __init__(self, title, overview):
        self.title = title
        self.overview = overview

class Movie(Media):
    def __init__(self, title, overview, release_year, director):
        super().__init__(title, overview)
        self.release_year = release_year
        self.director = director

class TVShow(Media):
    def __init__(self, title, overview, season):
        super().__init__(title, overview)
        self.season = season