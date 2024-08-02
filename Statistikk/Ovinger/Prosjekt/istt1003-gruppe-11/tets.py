import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from scipy import stats
import statsmodels.formula.api as smf
import statsmodels.api as sm

df = pd.read_csv("lego.population.csv", sep = ",", encoding = "latin1")
df
#%%
# fjerner forklaringsvariabler vi ikke trenger
df2 = df[['Set_Name', 'Theme', 'Pieces', 'Price', 'Pages', 'Minifigures', 'Unique_Pieces']]

# fjerner observasjoner med manglende datapunkter
df2 = df2.dropna()

df2.insert(7, "Gender", 'Unisex')

for row in range(0, len(df2['Theme'].values)):
    if (df2['Theme'].values[row] == "Friends" or
            df2['Theme'].values[row] == "Disney" or
            df2['Theme'].values[row] == "Unikitty" or
            df2['Theme'].values[row] == "LEGO Frozen 2" or
            df2['Theme'].values[row] == "Trolls World Tour" or
            df2['Theme'].values[row] == "Powerpuff Girls"):
        df2['Gender'].values[row] = 'Girl'

    if (df2['Theme'].values[row] == "NINJAGO" or
            df2['Theme'].values[row] == "Star Wars" or
            df2['Theme'].values[row] == "Marvel" or
            df2['Theme'].values[row] == "Batman" or
            df2['Theme'].values[row] == "Speed Champions" or
            df2['Theme'].values[row] == "Jurassic World" or
            df2['Theme'].values[row] == "Spider Man" or
            df2['Theme'].values[row] == "DC" or
            df2['Theme'].values[row] == "Monkie Kid" or
            df2['Theme'].values[row] == "Powered UP"):
        df2['Gender'].values[row] = 'Boy'


# gjør themes om til string og fjern alle tegn vi ikke vil ha med
df2['Theme'] = df2['Theme'].astype(str)
df2['Theme'] = df2['Theme'].str.replace(r'[^a-zA-Z0-9\s-]', '', regex = True)

# fjerner dollartegn og trademark-tegn fra datasettet
df2['Price'] = df2['Price'].str.replace('\$', '', regex = True)

# og gjør så prisen om til float
df2['Price'] = df2['Price'].astype(float)

y = df2['Pieces']
x = df2['Unique_Pieces']

x = sm.add_constant(x)

#modell = sm.OLS(y,x).fit()

#print(modell.summary())

formel = 'Unique_Pieces ~ Pieces*Gender'

modell = smf.ols(formel, data = df2)

resultat = modell.fit()

print(resultat.summary())
