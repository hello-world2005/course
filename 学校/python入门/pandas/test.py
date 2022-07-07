import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel('202206高一技术期末考统计.xlsx', sheet_name='技术成绩表')
df['qwq'] = 1
df1 = df.groupby('成绩', as_index = True)['qwq'].count()
x = df1.index
y = df1['qwq']
plt.bar(x, y)
plt.show()
