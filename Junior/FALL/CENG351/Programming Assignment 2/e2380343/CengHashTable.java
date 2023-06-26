import java.awt.image.AreaAveragingScaleFilter;
import java.lang.reflect.Array;
import java.util.ArrayList;

public class CengHashTable {

	private ArrayList<CengHashRow> table;
	private ArrayList<CengBucket> list;
	private int hashmod;
	private int bucketsize;
	private int globaldepth;


	private CengHashRow findRow(Integer pokekey){
		String bitrep = Integer.toBinaryString(pokekey % hashmod);
		int length = bitrep.length();
		for (int i = 0; i < Math.log(hashmod) / Math.log(2) - length; i++) {
			bitrep = "0" + bitrep;
		}

		bitrep = bitrep.substring(0,globaldepth);
		CengHashRow res = new CengHashRow("0",0);

		for (int i = 0; i < table.size(); i++) {
			if(table.get(i).hashPrefix().equals(bitrep)){
				res = table.get(i);
				return res;
			}
		}

		return res;
	}

	public CengHashTable()
	{
		this.hashmod = CengPokeKeeper.getHashMod();
		this.bucketsize = CengPokeKeeper.getBucketSize();
		CengHashRow  row = new CengHashRow("",0);
		table = new ArrayList<CengHashRow>();
		table.add(row);

		CengBucket newb = new CengBucket(bucketsize,0, hashmod);
		list = new ArrayList<CengBucket>();
		list.add(newb);
		globaldepth = 0;
	}

	public void deletePoke(Integer pokeKey)
	{
		CengHashRow row = this.findRow(pokeKey);

		list.get(row.getPointer()).delete(pokeKey);

		int count = 0;

		for (int i = 0; i < list.size(); i++) {
			if(list.get(i).getSize() == 0) count++;
		}
		System.out.print("\"delete\": {\n");
		System.out.print("\t\"emptyBucketNum\": " + count + "\n");
		System.out.println("}");
	}

	public void addPoke(CengPoke poke)
	{
		CengHashRow row = this.findRow(poke.pokeKey());
		int pt = row.getPointer();



		if (!list.get(row.getPointer()).isFull()){
			list.get(row.getPointer()).add(poke);
		}
		else{
			CengBucket newb = list.get(row.getPointer()).split(poke); //our split bucket
			list.add(newb); //bucket is added



			if(list.get(row.getPointer()).getDepth() > globaldepth) { //if we need doubling
				globaldepth++;
				int size = table.size();
				for (int i = 0; i < size; i++) {
					String pref = table.get(i).hashPrefix();
					CengHashRow newrow = new CengHashRow(pref + "1",table.get(i).getPointer());
					if (table.get(i).getPointer() == pt){

						newrow.setPointer(list.size()-1);
					}

					table.get(i).setPref(pref + "0");

					table.add(newrow);
				}
				this.sort();
			}
			else{

				ArrayList<Integer> rowsOfBucket = new ArrayList<>();
				for (int i = 0; i < table.size(); i++) {
					if (row.getPointer() == table.get(i).getPointer())
						rowsOfBucket.add(i);
				}


				for (int i = rowsOfBucket.size()/2 ; i < rowsOfBucket.size(); i++) {
					table.get(rowsOfBucket.get(i)).setPointer(list.size() - 1);
				}

			}
			this.addPoke(poke);
		}


	}
	
	public void searchPoke(Integer pokeKey)
	{
		CengHashRow row = this.findRow(pokeKey);
		CengBucket bucket = list.get(row.getPointer());
		ArrayList<Integer> rowstoprint = new ArrayList<Integer>();
		if (bucket.isIn(pokeKey)) {
			for (int i = 0; i < table.size(); i++) {
				if (row.getPointer() == table.get(i).getPointer()) {
					rowstoprint.add(i);
				}
			}
		}

		System.out.print("\"search\": {");
		System.out.print("\n");
		for (int j = 0; j < rowstoprint.size()-1; j++) {
			table.get(rowstoprint.get(j)).print(1);
			System.out.println(",");
		}
		if (rowstoprint.size() != 0){
			table.get(rowstoprint.get(rowstoprint.size()-1)).print(1);
		}



		System.out.println("\n}");
	}
	
	public void print()
	{


		System.out.print("\"table\": {\n");

		for (int i = 0; i < table.size()-1; i++) {
			table.get(i).print(1);
			System.out.print(",\n");
		}
		if (table.size()>0) {
			table.get(table.size()-1).print(1);
			System.out.print("\n");
		}

		System.out.println("}");
	}


	public CengBucket getBucket(int p){
		return list.get(p);
	}

	public void sort(){


		for (int i = 0; i < table.size(); i++) {
			String bitrep = Integer.toBinaryString(i);
			int length = bitrep.length();


			for (int j = 0; j < Math.log(table.size()) / Math.log(2) - length; j++) {
				bitrep = "0" + bitrep;
			}
			if (!table.get(i).hashPrefix().equals(bitrep)){
				int idx = sortHelper(bitrep);
				CengHashRow temp =  table.get(i);
				table.set(i,table.get(idx));
				table.set(idx,temp);
			}
		}
	}

	public int sortHelper(String rep){
		for (int i = 0; i < table.size(); i++) {
			if(table.get(i).hashPrefix().equals(rep)) return i;
		}
		return -1;
	}

	// GUI-Based Methods
	// These methods are required by GUI to work properly.

	public int prefixBitCount()
	{
		// TODO: Return table's hash prefix length.
		return 0;
	}

	public int rowCount()
	{
		// TODO: Return the count of HashRows in table.
		return 0;
	}

	public CengHashRow rowAtIndex(int index)
	{
		// TODO: Return corresponding hashRow at index.
		return null;
	}
}
