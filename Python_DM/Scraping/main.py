import os
from src.app import BeefAnalysis
from controller.CSVMerger import CSVMerger
from config.config import Config

Config = Config()
path = os.path.dirname(os.path.abspath(__file__))
spider_lists = Config.get('spider_lists')
spider_export_file = Config.get('export_filename')

for spider in spider_lists:
    with open(path + "/scraping_services/out/" + spider_export_file[spider], "w") as f:
        f.write("")

exec(open(path + "/bin/crawl.py").read())

csv_merger = CSVMerger()

header = ["product_name", "product_price"]

for spider in spider_lists:
    csv_merger.add(path + "/scraping_services/out/" + spider_export_file[spider], header, spider)

datasets = path + "/datasets/datasets.csv"

csv_merger.merge(datasets)

App = BeefAnalysis()
App.show(datasets)