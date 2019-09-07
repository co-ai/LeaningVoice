解题思路:

通过空格分割句子,遍历S查找符合条件的单词,输出



```java
import java.util.ArrayList;
import java.util.List;

public class Bigram{
    public static void main(String[] args) {
        Solution1 solution1 = new Solution1();
        System.out.println(solution1.findOcurrences("alice is a good girl she is a good student","is","a"));
    }
}

class Solution1 {
    public String[] findOcurrences(String text, String first, String second) {
        String[] S = text.split(" ");//分割单词
        
        List<String> list = new ArrayList<>();
        for(int i=0;i<S.length-2;i++){		//遍历S查找符合条件的单词
            if(S[i].equals(first)&&S[i+1].equals(second)) {
                list.add(S[i + 2]);
                i++;		//压入list
            }
        }
        String[] words = new String[list.size()];
        int ind=0;
        for(String str:list)
            words[ind++] = str;
        return words;
    }
}
```

