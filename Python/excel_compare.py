import pandas as pd

df_old = pd.read_excel('data_old.xlsx')
df_new = pd.read_excel('data_new.xlsx')
df_old['ver'] = 'old'
df_new['ver'] = 'new'

# set을 통해서 IP만 정렬하여 새로운 데이터와 옛날데이터를 뽑아냄
ip_dropped = set(df_old['IP']) - set(df_new['IP'])
ip_added = set(df_new['IP']) - set(df_old['IP'])

# isin 안에 리스트를 넣고 그 안에 있는 행을 전부 뽑아냄 
df_dropped = df_old[df_old['IP'].isin(ip_dropped)].iloc[:,:-1]
df_added = df_new[df_new['IP'].isin(ip_added)].iloc[:,:-1]

with pd.ExcelWriter('compared_result.xlsx') as writer:
   df_added.to_excel(writer, sheet_name='added', index=False)
   df_dropped.to_excel(writer, sheet_name='dropped', index=False)    
