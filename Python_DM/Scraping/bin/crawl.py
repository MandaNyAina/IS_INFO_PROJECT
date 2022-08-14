import os
from config.config import Config

Config = Config()

path = os.path.dirname(os.path.abspath(__file__))

spider_lists = Config.get('spider_lists')
spider_export_file = Config.get('export_filename')

os.chdir(path + '/scraping_services')

for spider in spider_lists:
    os.system(f"scrapy crawl {spider} -o out/{spider_export_file[spider]}")
