# 手动softmax回归
import numpy as np
import pandas as pd
from scipy import optimize
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import classification_report

# 加载数据
data = pd.read_csv('iris.csv')

# 定义特征和目标
features = ['Sepal.Length', 'Sepal.Width', 'Petal.Length', 'Petal.Width']
target = 'Species'

# 对目标标签进行编码
le = LabelEncoder()
data[target] = le.fit_transform(data[target])

# 获取特征和目标数组
X = data[features].values
y = data[target].values

n_classes = len(np.unique(y))  # 类别个数
n_each = 50  # 每类的样本数

# One-hot编码目标变量
def one_hot_encode(y):
    one_hot = np.zeros((y.size, y.max()+1))
    one_hot[np.arange(y.size), y] = 1
    return one_hot

y_one_hot = one_hot_encode(y)

# 获取训练集、验证集、测试集
indices = np.arange(len(data))
np.random.shuffle(indices)
train_indices = np.concatenate([indices[:n_each][:30], indices[n_each:2*n_each][:30], indices[2*n_each:][:30]])
val_indices = np.concatenate([indices[:n_each][30:40], indices[n_each:2*n_each][30:40], indices[2*n_each:][30:40]])
test_indices = np.concatenate([indices[:n_each][40:], indices[n_each:2*n_each][40:], indices[2*n_each:][40:]])

X_train, y_train = X[train_indices], y_one_hot[train_indices]
X_val, y_val = X[val_indices], y_one_hot[val_indices]
X_test, y_test = X[test_indices], y_one_hot[test_indices]

# 为X添加一列全为1的列（偏置项）
X_train = np.hstack([np.ones((X_train.shape[0], 1)), X_train])
X_val = np.hstack([np.ones((X_val.shape[0], 1)), X_val])
X_test = np.hstack([np.ones((X_test.shape[0], 1)), X_test])

# 初始化权重矩阵
theta = np.zeros((X_train.shape[1], n_classes))

# 确保在传递给优化函数前，theta被正确地reshape
theta_initial = theta.flatten()

# 定义softmax函数
def softmax(z):
    e_z = np.exp(z - np.max(z))
    return e_z / e_z.sum(axis=1, keepdims=True)

# 定义损失函数
def cost_function(theta, X, y):
    m = X.shape[0]
    # 重要：在计算之前将theta重塑为原始的 (5, 3) 形状
    theta = theta.reshape(X.shape[1], n_classes)
    logits = X.dot(theta)
    prob = softmax(logits)
    cost = (-1 / m) * np.sum(y * np.log(prob + 1e-5)) + 1e-4 * np.sum(theta**2)
    return cost

# 定义梯度函数
def gradient(theta, X, y):
    m = X.shape[0]
    # 重要：在计算之前将theta重塑为原始的 (5, 3) 形状
    theta = theta.reshape(X.shape[1], n_classes)
    logits = X.dot(theta)
    prob = softmax(logits)
    grad = (-1 / m) * X.T.dot(y - prob) + 1e-4 * theta
    return grad.flatten()

# # 展开theta以便使用optimize.minimize
# theta_initial = theta.flatten()

# 调用优化函数
result = optimize.minimize(fun=cost_function, x0=theta_initial, args=(X_train, y_train), method='TNC', jac=gradient)

# 获取优化后的theta
optimal_theta = result.x.reshape(X_train.shape[1], n_classes)

# 预测函数
def predict(X, theta):
    return np.argmax(softmax(X.dot(theta)), axis=1)

# 进行预测
y_train_pred = predict(X_train, optimal_theta)
y_val_pred = predict(X_val, optimal_theta)
y_test_pred = predict(X_test, optimal_theta)

# 将one-hot编码转换回标签
y_train_actual = np.argmax(y_train, axis=1)
y_val_actual = np.argmax(y_val, axis=1)
y_test_actual = np.argmax(y_test, axis=1)

# 输出每个数据集的分类报告
print("训练集的分类报告:")
print(classification_report(y_train_actual, y_train_pred, target_names=le.classes_))

print("验证集的分类报告:")
print(classification_report(y_val_actual, y_val_pred, target_names=le.classes_))

print("测试集的分类报告:")
print(classification_report(y_test_actual, y_test_pred, target_names=le.classes_))