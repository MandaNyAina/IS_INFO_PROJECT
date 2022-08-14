
import csv
from .CSVReader import CSVReader

class CSVMerger:
    data: list = list()

    def add(self, csv_filename: str, header: list, key:str=""):
        data = CSVReader().loads(csv_filename, header)
        if key != "":
            for value in data:
                value["key"] = key   
        self.data += data

    def merge(self, output_path: str):
        with open(output_path, "w") as output_file:
            output_file.write("")
            writer = csv.writer(output_file)
            if len(self.data):
                writer.writerow(self.data[0].keys())
                for value in self.data:
                    writer.writerow(value.values())