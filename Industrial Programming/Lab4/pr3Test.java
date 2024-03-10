import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class pr3Test {

    @org.junit.jupiter.api.Test
    void findLexemes() {
        ArrayList<String> StringOfLexemes = new ArrayList<>();
        StringOfLexemes.add("ruewi");
        StringOfLexemes.add("tre");
        StringOfLexemes.add("ru23ew35i");
        StringOfLexemes.add(")9532");
        assertEquals(StringOfLexemes, pr3.findLexemes("ruewi ,./ . tre /./. ., ru23ew35i /./, ,./)9532", "/,. ", new int[100], 0, new StringBuilder(), new StringBuilder(), new StringBuilder()));
    }

    @org.junit.jupiter.api.Test
    void deleteParentheses() {
        assertEquals(0, new StringBuilder("tyrwuittwuei etw").compareTo(pr3.deleteParentheses("tyrwuittwuei etw")));
        assertEquals(0, new StringBuilder("tyrwuit etw").compareTo(pr3.deleteParentheses("tyrwuit(twuei) etw")));
        assertEquals(0, new StringBuilder("tyrwuit").compareTo(pr3.deleteParentheses("tyrwuit(twuei)( etw)")));
        assertEquals(0, new StringBuilder("tyrwuit").compareTo(pr3.deleteParentheses("tyrwuit(twuei() etw)")));
        assertEquals(0, new StringBuilder("tyrwuit)twuei etw(").compareTo(pr3.deleteParentheses("tyrwuit)twuei etw(")));
    }

    @org.junit.jupiter.api.Test
    void sort() {
        ArrayList<String> StringOfLexemes = new ArrayList<>();
        StringOfLexemes.add("rer");
        StringOfLexemes.add("trert");
        StringOfLexemes.add("tyrr");
        StringOfLexemes.add("123");
        ArrayList<String> StringOfLexemes1 = new ArrayList<>();
        StringOfLexemes1.add("tyrr");
        StringOfLexemes1.add("trert");
        StringOfLexemes1.add("rer");
        StringOfLexemes1.add("123");
        pr3.sort(StringOfLexemes1);
        assertEquals(StringOfLexemes, StringOfLexemes1);
    }

    @org.junit.jupiter.api.Test
    void isNumber() {
        assertFalse(pr3.isNumber("rew"));
        assertFalse(pr3.isNumber("rew123"));
        assertFalse(pr3.isNumber("rew 5235"));
        assertTrue(pr3.isNumber("432"));
        assertTrue(pr3.isNumber("1"));
        assertTrue(pr3.isNumber("-534"));
        assertFalse(pr3.isNumber("432.543"));
    }

    @org.junit.jupiter.api.Test
    void isPalindrome() {
        assertFalse(pr3.isPalindrome("rew"));
        assertFalse(pr3.isPalindrome("123"));
        assertFalse(pr3.isPalindrome("rew 5235"));
        assertTrue(pr3.isPalindrome("a"));
        assertTrue(pr3.isPalindrome("242"));
        assertTrue(pr3.isPalindrome("retter"));
        assertTrue(pr3.isPalindrome("ut7667tu"));
        assertTrue(pr3.isPalindrome("'[./((/.['"));
    }
}