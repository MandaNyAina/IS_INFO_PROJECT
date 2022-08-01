annee_naissance = {2015: {1960: 2, 2000: 20}, 2016: {1960: 3, 2000: 12}, 2017: {1980: 2, 2001: 4}}

def calculate_age_by_birth_with_given_year(birth_year: int, given_year: int) -> int:
    """Calculate age from birt year by given year"""
    return abs(given_year - birth_year)

def get_average_by_year(year: int) -> int:
    """Calculate average of etudiant"""
    tmp_value = 0
    sum_of_etudiant = 0
    etudiants = annee_naissance[year]
    for etudiant_year in etudiants:
        etudiant_number = etudiants[etudiant_year]
        sum_of_etudiant += int(etudiant_number)
        tmp_value += (calculate_age_by_birth_with_given_year(etudiant_year, year) * etudiant_number)
    return round(tmp_value / sum_of_etudiant, 2)

result = dict()
for annee in annee_naissance:
    result[annee] = get_average_by_year(annee)

print(result)