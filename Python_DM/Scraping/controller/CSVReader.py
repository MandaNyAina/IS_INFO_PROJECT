import csv

class CSVReader:

    def loads(self, filename: str, header: list) -> list:
        output = list()
        with open(filename) as csv_file:
            data = csv.DictReader(csv_file, delimiter=",", fieldnames=header)
            for value in data:
                output.append(dict(value))
        del output[0]
        return output