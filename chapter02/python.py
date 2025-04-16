import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib

matplotlib.rc("font", family='AppleGothic')
matplotlib.rcParams['axes.unicode_minus'] = False

df = pd.read_excel("./house.xlsx")

villa_sale = df[(df['구분'] == '빌라') & (df['가격구분'] == '매매')]
apt_sale = df[(df['구분'] == '아파트') & (df['가격구분'] == '매매')]

# 연습 a 빌라 매매 가격 통계
print("빌라 매매")
print("평균:", villa_sale['가격'].mean())
print("최댓값:", villa_sale['가격'].max())
print("최솟값:", villa_sale['가격'].min())
print("표준편차:", villa_sale['가격'].std())

# 연습 b 빌라 매매 가격 통계
print("아파트 매매")
print("평균:", villa_sale['가격'].mean())
print("최댓값:", villa_sale['가격'].max())
print("최솟값:", villa_sale['가격'].min())
print("표준편차:", villa_sale['가격'].std())

# 연습 c 가격 분포 비교
fig, axes = plt.subplots(nrows=2, ncols=1, sharex=True, figsize=(8, 6))

sns.histplot(x='가격', data=villa_sale, kde=True, ax=axes[0], color='skyblue')
axes[0].set_title('빌라 매매 가격 분포')

sns.histplot(x='가격', data=apt_sale, kde=True, ax=axes[1], color='salmon')
axes[1].set_title('아파트 매매 가격 분포')

plt.tight_layout()
plt.show()