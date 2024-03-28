# K-means，类封装
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

class KMeansClassifier:
    def __init__(self, k=3, max_iters=100, random_state=50):
        self.k = k  # 簇的个数
        self.max_iters = max_iters
        self.random_state = random_state  # 初始化随机种子
        self.centroids = None

    # 训练模型
    def fit(self, X):
        np.random.seed(self.random_state)
        # 随机初始化质心
        rand_indices = np.random.permutation(X.shape[0])[:self.k]
        self.centroids = X[rand_indices]

        for _ in range(self.max_iters):
            # 分配样本到最近的质心
            clusters = self._assign_clusters(X)
            # 记录上一次的质心位置
            prev_centroids = self.centroids.copy()
            # 重新计算质心
            self.centroids = self._compute_centroids(X, clusters)
            # 如果质心不再变化，提前终止
            if np.all(prev_centroids == self.centroids):
                break

    # 样本分配到最近的质心
    def _assign_clusters(self, X):
        distances = self._compute_distances(X, self.centroids)
        return np.argmin(distances, axis=1)

    def _compute_distances(self, X, centroids):
        distances = np.zeros((X.shape[0], self.k))
        for i, centroid in enumerate(centroids):
            distances[:, i] = np.linalg.norm(X - centroid, axis=1)
        return distances

    def _compute_centroids(self, X, clusters):
        centroids = np.zeros((self.k, X.shape[1]))
        for i in range(self.k):
            centroids[i] = X[clusters == i].mean(axis=0)
        return centroids

    def predict(self, X):
        return self._assign_clusters(X)


data = pd.read_csv('iris.csv')
X = data.iloc[:, :-1].values
print(data.info())

# 创建k-means实例
kmeans = KMeansClassifier(k=3)

# 训练k-means模型
kmeans.fit(X)

# 预测
labels = kmeans.predict(X)

# 取第三列和第四列特征进行可视化
# 这里的颜色是通过cmap='viridis'自动生成的喔
plt.scatter(X[:, 2], X[:, 3], c=labels, cmap='viridis')
plt.xlabel('花瓣长度 (Petal Length)')
plt.ylabel('花瓣宽度 (Petal Width)')
plt.title('鸢尾花数据的K均值聚类 (K-Means Clustering of Iris Data)')

# 给每个类别的花加上标签
class_names = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']
for i, class_name in enumerate(class_names):
    plt.scatter([], [], label=class_name)

plt.legend(scatterpoints=1, frameon=False, labelspacing=1, title='花的种类 (Flower Types)')
plt.scatter(kmeans.centroids[:, 2], kmeans.centroids[:, 3], c='red', s=100, alpha=0.75)  # 质心
plt.show()