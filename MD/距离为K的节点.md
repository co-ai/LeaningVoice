题目描述:

给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。

返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。



思路:

没有思路...

参考网上博客题解的方法,把二叉树转化为无向图,然后对无向图进行BFS,找出到target节点距离为K的所有节点。

难点就是如何将二叉树转化为无向图。



博客中用DFS把树转化为图的方法，真看不懂

```c++
private void buidGraphDFS(TreeNode parent, TreeNode child) {
        if (child == null)
            return;
        if (parent != null) {
            List<TreeNode> neighborP = graph.getOrDefault(parent, new ArrayList<>());
            //
            neighborP.add(child);
            graph.put(parent, neighborP);

            List<TreeNode> neighborC = graph.getOrDefault(child, new ArrayList<>());
            neighborC.add(parent);
            graph.put(child, neighborC);
        }
        buidGraphDFS(child, child.left);
        buidGraphDFS(child, child.right);
    }
```



