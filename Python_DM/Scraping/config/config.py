import json, os

class Config:
    env_file: dict = dict()

    def __init__(self) -> None:
        path = os.path.dirname(os.path.abspath(__file__))
        with open(path + '/env.json') as env:
            self.env_file = json.load(env)

    def get(self, config_name: str):
        if config_name in self.env_file.keys():
            return self.env_file[config_name]
        else:
            return None