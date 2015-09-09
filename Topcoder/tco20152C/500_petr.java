//from petr
//http://mayokoex.hatenablog.com/entry/2015/07/25/110716 another solution
import java.util.List;
import java.util.ArrayList;
 
/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class LongSeat {
    static class Element {
        long maxSum;
        int freeChildren;
        List<Element> constrainedChildren = new ArrayList<>();
 
        Element cloneIt(Element insertAt, long len) {
            Element res = new Element();
            res.maxSum = maxSum;
            res.freeChildren = freeChildren;
            res.constrainedChildren = new ArrayList<>(constrainedChildren.size());
            for (Element child : constrainedChildren) {
                Element childClone = child.cloneIt(insertAt, len);
                if (childClone.maxSum < child.maxSum) {
                    res.maxSum -= len;
                }
                res.constrainedChildren.add(childClone);
            }
            if (this == insertAt) {
                ++res.freeChildren;
                res.maxSum -= len;
            }
            return res;
        }
 
        public long totalSizeIfBlocking(long len) {
            long res = freeChildren * (len - 1);
            for (Element child : constrainedChildren) {
                res += child.totalSizeIfBlocking(len);
            }
            return Math.min(res, maxSum);
        }
 
        public void updateBlocking(long len) {
            if (freeChildren == 1 && constrainedChildren.isEmpty()) {
                maxSum = Math.min(maxSum, len - 1);
            } else {
                for (Element child : constrainedChildren) child.updateBlocking(len);
                for (int i = 0; i < freeChildren; ++i) {
                    Element child = new Element();
                    child.maxSum = len - 1;
                    child.freeChildren = 1;
                    constrainedChildren.add(child);
                }
                freeChildren = 0;
            }
        }
    }
 
    static final long BUBEN = 1000;
 
    public String[] canSit(int L, int[] width) {
        boolean[] sit = new boolean[width.length];
        boolean[] stand = new boolean[width.length];
        Element tree = new Element();
        tree.maxSum = L * BUBEN;
        tree.freeChildren = 1;
        rec(tree, 0, width, sit, stand);
        String[] res = new String[width.length];
        for (int i = 0; i < width.length; ++i)
            if (!sit[i])
                res[i] = "Stand";
            else if (!stand[i])
                res[i] = "Sit";
            else
                res[i] = "Unsure";
        return res;
    }
 
    private void rec(Element tree, int pos, int[] width, boolean[] sit, boolean[] stand) {
        if (pos >= width.length) return;
        long len = width[pos] * BUBEN;
        if (tree.totalSizeIfBlocking(len) == tree.maxSum) {
            Element newTree = tree.cloneIt(null, 0);
            newTree.updateBlocking(len);
            stand[pos] = true;
            rec(newTree, pos + 1, width, sit, stand);
        }
        traverse(tree, tree.maxSum, tree, pos, width, sit, stand);
    }
 
    private void traverse(Element tree, long curMax, Element at, int pos, int[] width, boolean[] sit, boolean[] stand) {
        long len = width[pos] * BUBEN;
        curMax = Math.min(curMax, at.maxSum);
        if (curMax < len) return;
        if (at.freeChildren > 0) {
            sit[pos] = true;
            Element newTree = tree.cloneIt(at, len);
            rec(newTree, pos + 1, width, sit, stand);
        }
        for (Element child : at.constrainedChildren) {
            traverse(tree, curMax, child, pos, width, sit, stand);
        }
    }
}
