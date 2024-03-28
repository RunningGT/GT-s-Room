import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score

# 读取数据集
data = pd.read_csv('housing.csv')
print(data.info())

# 绘制数据集中每个数值型特征的直方图
data.hist(bins=50, figsize=(20, 15))
plt.show()

# 归一化处理
num_features = data.select_dtypes(include=[np.number]).columns
data[num_features] = (data[num_features] - data[num_features].mean()) / data[num_features].std()

# 分箱
data['DIS'] = pd.cut(data['DIS'], bins=5, labels=False)

# 去除离群值
for feature in num_features:
    data = data[np.abs(data[feature]) <= 3]

# 选取特征
selected_features = ['CRIM', 'ZN', 'INDUS', 'LSTAT', 'RM', 'AGE', 'DIS', 'RAD', 'TAX', 'PIRATIO']
X = data[selected_features]
y = data['MEDV']

# 随机划分数据集为训练、验证和测试集
X_train_val, X_test, y_train_val, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
X_train, X_val, y_train, y_val = train_test_split(X_train_val, y_train_val, test_size=0.25, random_state=42)  # 0.25 * 0.8 = 0.2

# 确认数据集划分情况
assert len(X_train) == int(len(X) * 0.6)
assert len(X_val) == len(X_test) == int(len(X) * 0.2)

# cost函数（L2正则化）
def computeCost(X, y, theta, lambda_):
    m = len(y)
    errors = X @ theta - y
    regularization = (lambda_ / (2 * m)) * np.sum(np.square(theta[1:]))  # 舍弃第一个参数,因为截距项不进行正则化
    cost = (1 / (2 * m)) * np.sum(np.square(errors)) + regularization
    return cost

# 梯度下降函数（L2正则化）
def gradientDescent(X, y, theta, alpha, iters, lambda_):
    m = len(y)
    cost_history = [0] * iters
    for i in range(iters):
        prediction = X.dot(theta)
        theta = theta * (1 - alpha * (lambda_ / m)) - alpha * (1 / m) * X.T.dot(prediction - y)
        cost_history[i] = computeCost(X, y, theta, lambda_)
    return theta, cost_history

# 初始化参数theta
theta = np.zeros(X_train.shape[1])

# 设置参数
alpha = 0.001
iters = 1000
lambda_ = 100

# 运行梯度下降算法
theta, cost_history = gradientDescent(X_train, y_train, theta, alpha, iters, lambda_)

# 验证集的预测
y_pred_val = X_val.dot(theta)

# 测试集的预测
y_pred_test = X_test.dot(theta)

# 计算训练集、验证集和测试集的成本和R^2值
train_cost = computeCost(X_train, y_train, theta, lambda_)
val_cost = computeCost(X_val, y_val, theta, lambda_)
test_cost = computeCost(X_test, y_test, theta, lambda_)
train_r_squared = r2_score(y_train, X_train.dot(theta))
val_r_squared = r2_score(y_val, y_pred_val)
test_r_squared = r2_score(y_test, y_pred_test)

# 输出训练集、验证集和测试集的成本和R^2值
print('训练集cost:', train_cost)
print('训练集R^2:', train_r_squared)
print('验证集cost:', val_cost)
print('验证集R^2:', val_r_squared)
print('测试集cost:', test_cost)
print('测试集R^2:', test_r_squared)

# 绘制成本变化图
plt.figure(figsize=(12, 8))
plt.plot(cost_history)
plt.ylabel('cost')
plt.xlabel('迭代次数')
plt.title('迭代过程中的cost变化')
plt.show()
