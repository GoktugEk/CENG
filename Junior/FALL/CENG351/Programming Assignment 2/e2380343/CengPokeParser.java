import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class CengPokeParser {



	public static ArrayList<CengPoke> parsePokeFile(String filename)
	{
		ArrayList<CengPoke> pokeList = new ArrayList<CengPoke>();
		return pokeList;
	}
	
	public static void startParsingCommandLine() throws IOException
	{
		// TODO: Start listening and parsing command line -System.in-.
		// There are 5 commands:
		// 1) quit : End the app. Print nothing, call nothing.
		// 2) add : Parse and create the poke, and call CengPokeKeeper.addPoke(newlyCreatedPoke).
		// 3) search : Parse the pokeKey, and call CengPokeKeeper.searchPoke(parsedKey).
		// 4) delete: Parse the pokeKey, and call CengPokeKeeper.removePoke(parsedKey).
		// 5) print : Print the whole hash table with the corresponding buckets, call CengPokeKeeper.printEverything().

		// Commands (quit, add, search, print) are case-insensitive.

		Scanner scanner = new Scanner(System.in);
		while(scanner.hasNext()){
			String[] line = scanner.nextLine().split("\t");
			String command = line[0];




			if(command.equals("quit")){
				break;
			}
			else if (command.equals("add")){
				int pokekey = Integer.parseInt(line[1]);
				String pokename = line[2];
				String pokepower = line[3];
				String poketype = line[4];

				CengPoke pokemon = new CengPoke(pokekey,pokename,pokepower,poketype);

				CengPokeKeeper.addPoke(pokemon);
			}
			else if (command.equals("search")){
				int pokekey = Integer.parseInt(line[1]);


				CengPokeKeeper.searchPoke(pokekey);
			}
			else if (command.equals("delete")){
				int pokekey = Integer.parseInt(line[1]);
				
				CengPokeKeeper.deletePoke(pokekey);
			}
			else  if(command.equals("print")){
				CengPokeKeeper.printEverything();
			}

			


		}
	}


}
