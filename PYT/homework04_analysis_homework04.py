import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

"""
Dataset obsahuje nasledujici promenne:
 'Age' - vek v rocich
 'Fare' - cena jizdenky
 'Name' - jmeno cestujiciho
 'Parch' - # rodicu/deti daneho cloveka na palube
 'PassengerId' - Id
 'Pclass' - Trida, 1 = 1. trida, 2 = 2.trida, 3 = 3.trida
 'Sex' - pohlavi
 'SibSp' - # sourozencu/manzelu daneho cloveka na ppalube
 'Survived' - 0 = Neprezil, 1 = Prezil
 'Embarked' - Pristav, kde se dany clovek nalodil. C = Cherbourg, Q = Queenstown, S = Southampton
 'Cabin' - Cislo kabiny
 'Ticket' - Cislo tiketu
"""

def load_dataset(train_file_path, test_file_path):
    """
    Napiste funkci, ktera nacte soubory se souboru zadanych parametrem a vytvori dva separatni DataFrame. Pro testovani vyuzijte data 'data/train.csv' a 'data/test.csv'
    Ke kazdemu dataframe pridejte sloupecek pojmenovaný jako "Label", ktery bude obsahovat hodnoty "Train" pro train.csv a "Test" pro test.csv.

    1. Pote slucte oba dataframy.
    2. Z vysledneho slouceneho DataFramu odstraňte sloupce  "Ticket", "Embarked", "Cabin".
    3. Sloučený DataDrame bude mít index od 0 do do počtu řádků.
    4. Vratte slouceny DataDrame.
    """

    train = pd.read_csv(train_file_path)
    test = pd.read_csv(test_file_path)
    train['Label'] = "Train"
    test['Label'] = "Test"

    return train.append(test, ignore_index=True, sort=True).drop(columns=["Ticket", "Embarked", "Cabin"])

def get_missing_values(df : pd.DataFrame) -> pd.DataFrame:
    """
    Ze zadaneho dataframu zjistete chybejici hodnoty. Vyvorte DataFrame, ktery bude obsahovat v indexu jednotlive promenne
    a ve prvnim sloupci bude promenna 'Total' obsahujici celkovy pocet chybejicich hodnot a ve druhem sloupci promenna 'Percent',
    ve ktere bude procentualni vyjadreni chybejicich hodnot vuci celkovemu poctu radku v tabulce.
    DataFrame seradte od nejvetsich po nejmensi hodnoty.
    Vrattre DataFrame chybejicich hodnot a celkovy pocet chybejicich hodnot.

    Priklad:

               |  Total  |  Percent
    "Column1"  |   34    |    76
    "Column2"  |   0     |    0

    """
    total = df.isna().sum().to_numpy(dtype = int)
    percent = total / df.shape[0]
    output = pd.DataFrame(columns = ['Total', 'Percent'], index = df.columns.values, data = np.column_stack((total, percent * 100)))

    return output.sort_values(list(output.columns.values), ascending=False)

def substitute_missing_values(df: pd.DataFrame) -> pd.DataFrame:
    """
    Chybejici hodnoty ve sloupecku "Age" nahradte meanem hodnot z "Age".
    Chybejici hodnoty ve sloupecku "Fare" nahradte meadianem hodnot z "Fare".
    V jednom pripade pouzijte "loc" a ve druhem "fillna".
    Zadany DataFrame neupravujte, ale vytvorte si kopii.
    Vratte upraveny DataFrame.
    """

    output = df.fillna({'Age': df['Age'].mean()})
    output.loc[np.isnan(output['Fare'])] = output['Fare'].median()

    return output

def get_correlation(df: pd.DataFrame) -> float:
    """
    Spocitejte korelaci pro "Age" a "Fare" a vratte korelaci mezi "Age" a "Fare".
    """

    return df['Age'].corr(df['Fare'])

def get_survived_per_class(df : pd.DataFrame, group_by_column_name : str) ->pd.DataFrame:
    """
    Spocitejte prumer z promenne "Survived" pro kazdou skupinu zadanou parametrem "group_by_column_name".
    Hodnoty seradte od nejvetsich po mejmensi.
    Hodnoty "Survived" zaokhroulete na 2 desetinna mista.
    Vratte pd.DataFrame.

    Priklad:

    get_survived_per_class(df, "Sex")

                 Survived
    Male     |      0.32
    Female   |      0.82

    """

    group_name_df = df.groupby(group_by_column_name).mean()['Survived']
    output = pd.DataFrame(columns = [group_by_column_name], data = group_name_df.index.to_numpy())
    output['Survived'] = np.round(group_name_df.values, 2)

    return output.sort_values('Survived', ascending = False)

def get_outliers(df: pd.DataFrame) -> (int, str):
    """
    Vyfiltrujte odlehle hodnoty (outliers) ve sloupecku "Fare" pomoci metody IRQ.
    Tedy spocitejte rozdil 3. a 1. kvantilu, tj. IQR = Q3 - Q1.
    Pote odfiltrujte vsechny hodnoty nesplnujici: Q1 - 1.5*IQR < "Fare" < Q3 + 1.5*IQR.
    Namalujte box plot pro sloupec "Fare" pred a po vyfiltrovani outlieru.
    Vratte tuple obsahujici pocet outlieru a jmeno cestujiciho pro nejvetsi outlier.
    """

    Q1 = df['Fare'].quantile(0.25)
    Q3 = df['Fare'].quantile(0.75)
    IQR = Q3 - Q1

    low = Q1 - 1.5 * IQR
    high = Q3 + 1.5 * IQR
    output = df.loc[(df['Fare'] <= low) | (df['Fare'] >= high)]

    plt.boxplot([df['Fare'].dropna().tolist(), output['Fare'].dropna().tolist()])

    return output.shape[0], output.loc[output['Fare'].idxmax()]['Name']


def normalise(df: pd.DataFrame, col: str) -> pd.DataFrame:
    """
    Naskalujte sloupec "col" zadany parametrem pro kazdou "Pclass" hodnotu z dataframu "df" zvlast.
    Pouzijte vzorec: scaled_x_i = (x_i - min(x)) / (max(x) - min(x)), kde "x_i" prestavuje konkretni hodnotu ve sloupeci "col".
    Vratte naskalovany dataframe.
    """

    output = df

    for i in df['Pclass'].unique():
        column = df.loc[df['Pclass'] == i, [col]]
        output.loc[df['Pclass'] == i, [col]] = (column - column.min())/(column.max() - column.min())

    return output


def create_new_features(df: pd.DataFrame) -> pd.DataFrame:
    """
    Vytvorte 3 nove promenne:
    1. "Fare_scaled" - vytvorte z "Fare" tak, aby mela nulovy prumer a jednotkovou standartni odchylku.
    2. "Age_log" - vytvorte z "Age" tak, aby nova promenna byla logaritmem puvodni "Age".
    3. "Sex" - Sloupec "Sex" nahradte: "female" -> 1, "male" -> 0, kde 0 a 1 jsou integery.

    Nemodifikujte predany DataFrame, ale vytvorte si novy, upravte ho a vratte jej.
    """
    output = df

    output['Fare_scaled'] = (output['Fare'] - output['Fare'].mean()) / np.std(output['Fare'])
    output['Age_log'] = np.log(output['Age'])
    output['Sex'] = (output['Sex'] == 'female')

    return output

def determine_survival(df: pd.DataFrame, n_interval: int, age: float, sex: str) -> float:
    """
    Na zaklade statistickeho zpracovani dat zjistete pravdepodobnost preziti Vami zadaneho cloveka (zadava se vek a pohlavi pomoci parametru "age" a "sex")

    Vsechny chybejici hodnoty ve vstupnim DataFramu ve sloupci "Age" nahradte prumerem.
    Rozdelte "Age" do n intervalu zadanych parametrem "n_interval". Napr. pokud bude Age mit hodnoty [2, 13, 18, 25] a mame jej rozdelit do 2 intervalu,
    tak bude vysledek:

    0    (1.977, 13.5]
    1    (1.977, 13.5]
    2     (13.5, 25.0]
    3     (13.5, 25.0]

    Pridejte k rozdeleni jeste pohlavi. Tj. pro kazdou kombinaci pohlavi a intervalu veku zjistete prumernou
    pravdepodobnost preziti ze sloupce "Survival" a tu i vratte.

    Vysledny DataFrame:

    "AgeInterval"   |    "Sex"    |   "Survival Probability"
       (0-10)       | "male"      |            0.21
       (0-10)       | "female"    |            0.28
       (10-20)      | "male"      |            0.10
       (10-20)      | "female"    |            0.15
       atd...

    Takze vystup funkce determine_survival(df, n_interval=20, age = 5, sex = "male") bude 0.21. Tato hodnota bude navratovou hodnotou funkce.

    """

    df = df.fillna({'Age': df['Age'].mean()})
    intervals = np.linspace(df['Age'].min(), df['Age'].max(), n_interval + 1)

    AgeIntervals = [(intervals[i], intervals[i + 1]) 
                    for i in range(0, intervals.shape[0] - 1) 
                        for j in (0, 1)] #male ande female intervals
    sexes = []
    for i in range(len(AgeIntervals)) :
        if i % 2 == 0 : sexes.append('male')
        else : sexes.append('female')

    output = 0.0
    survival_probabilities = []
    for interval, it_sex in zip(AgeIntervals, sexes):
        probability = df.loc[(df['Age'] > interval[0]) & (df['Age'] <= interval[1]) & (df['Sex'] == it_sex), ['Survived']].mean()['Survived']
        survival_probabilities.append(probability)

        if output == 0.0 and interval[0] < age <= interval[1] and it_sex == sex:
            output = probability

    output_df = pd.DataFrame()

    output_df['AgeInterval'] = AgeIntervals
    output_df['Sex'] = sexes
    output_df['Survival Probability'] = survival_probabilities

    return output
