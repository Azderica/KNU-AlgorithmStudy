import java.util.*;

class pos{
	int y;
	int x;
	public pos(int y, int x) {
		this.y = y;
		this.x = x;
	}
}

public class Main {
	static final int MAX = 9;
	static int board[][] = new int[MAX][MAX];
	static ArrayList<pos> blankList = new ArrayList<>();	// ��ĭ ��ġ
	
	static void dfs(ArrayList<pos> arr, int idx) {
		if(idx == blankList.size()) {
			for(int i=0; i<MAX; i++) {
				for(int j=0; j<MAX; j++) {
					System.out.print(board[i][j] + " ");
				}
				System.out.println("");
			}
			System.exit(0);
		}
		
		// 1~9���� �������� ���ɼ� Ȯ��
		for(int i=1; i<=MAX; i++) {
			if(isValidPos(arr, idx, i)) {
				board[arr.get(idx).y][arr.get(idx).x] = i;
				dfs(arr, idx + 1);
			}
			if(i == MAX)
				board[arr.get(idx).y][arr.get(idx).x] = 0;
		}
	}
	
	static boolean isValidPos(ArrayList<pos> arr, int idx, int num) {
		for(int j=0; j<MAX; j++) {		// ����
			if(arr.get(idx).x == j)	
				continue;
			if(board[arr.get(idx).y][j] == num)	
				return false;
		}
		for(int i=0; i<MAX; i++) {		// ����
			if(arr.get(idx).y == i)	
				continue;
			if(board[i][arr.get(idx).x] == num)	
				return false;
		}
		int y = (arr.get(idx).y/3) * 3;
		int x = (arr.get(idx).x/3) * 3;
		for(int i=y; i<y+3; i++) {
			for(int j=x; j<x+3; j++) {
				if(i == arr.get(idx).y && j == arr.get(idx).x)	
					continue;
				if(board[i][j] != 0 && board[i][j] == num)	
					return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		// ������ board ä���
		for(int i=0; i<MAX; i++)
			for(int j=0; j<MAX; j++)
				board[i][j] = sc.nextInt();
		
		// ������ ��ĭ�� Array List�� ����
		for(int i=0; i<MAX; i++)
			for(int j=0; j<MAX; j++)
				if(board[i][j] == 0)
					blankList.add(new pos(i, j));
		
		//for(int i=0; i<MAX; i++)
		//	System.out.print(blankList.get(i).y + ", " + blankList.get(i).x + "  ");
		//System.out.println("");
		
		// dfs, 0��° �ε������� ������ ���� ä������.
		dfs(blankList, 0);
		
	}

}
