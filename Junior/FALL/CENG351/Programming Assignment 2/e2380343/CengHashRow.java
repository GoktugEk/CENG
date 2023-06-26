public class CengHashRow {

	private String pref;
	private int pointer;



	public CengHashRow(String pref, int pointer){
		this.pref = pref;
		this.pointer = pointer;
	}

	public String hashPrefix()
	{
		return pref;
	}

	public void printTab(int tab){
		for (int i = 0; i < tab; i++) {
			System.out.print("\t");
		}
	}

	public void print(int tab){
		CengBucket bucket =  CengPokeKeeper.getHashTable().getBucket(pointer);
		printTab(tab);
		System.out.print("\"row\": {\n");
		printTab(tab+1);
		if (pref.equals(""))
		System.out.print("\"hashPref\": " + 0 + ",\n");
		else
		System.out.print("\"hashPref\": " + pref + ",\n");
		bucket.print(tab+1);
		printTab(tab);
		System.out.print("}");
	}


	public int getPointer() {
		return pointer;
	}

	public void setPref(String pref) {
		this.pref = pref;
	}

	public void setPointer(int pointer) {
		this.pointer = pointer;
	}


	public CengBucket getBucket()
	{
		// TODO: Return the bucket that the row points at.
		return null;
	}

	public boolean isVisited()
	{
		// TODO: Return whether the row is used while searching.
		return false;
	}
	// Own Methods
}
