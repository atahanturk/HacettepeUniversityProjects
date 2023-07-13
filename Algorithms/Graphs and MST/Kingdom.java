import java.io.*;
import java.util.*;


public class Kingdom {

    // TODO: You should add appropriate instance variables.
    public int[][] adjacencyMatrix;
    public boolean[] visited;
    public void initializeKingdom(String filename){
        // Read the txt file and fill your instance variables
        // TODO: Your code here
        List<String> lines = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                lines.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        int size = lines.size();
        adjacencyMatrix = new int[size][size];

        for (int row = 0; row < size; row++) {
            String[] values = lines.get(row).trim().split("\\s+");
            for (int column = 0; column < size; column++) {
                adjacencyMatrix[row][column] = Integer.parseInt(values[column]);
            }
        }

    }

    public List<Colony> getColonies() {
        List<Colony> colonies = new ArrayList<>();
        // TODO: DON'T READ THE .TXT FILE HERE!
        // Identify the colonies using the given input file.
        // TODO: Your code here
        int size = adjacencyMatrix.length;
        visited = new boolean[size];

        for (int city = 1; city < size+1; city++) {
            if (!visited[city - 1]) {
                Colony colony = new Colony();
                dfs(city, colony);
                colonies.add(colony);
            }
        }

        return colonies;
    }

    public void dfs(int city, Colony colony) {
        visited[city - 1] = true;
        colony.cities.add(city);
        colony.roadNetwork.put(city, new ArrayList<>());
        int size = adjacencyMatrix.length;

        for (int neighbour = 1; neighbour < size+1; neighbour++) {
            if (adjacencyMatrix[city - 1][neighbour - 1] == 1) {
                colony.roadNetwork.get(city).add(neighbour);
            }
            if ((adjacencyMatrix[city - 1][neighbour - 1] == 1 || adjacencyMatrix[neighbour - 1][city - 1] == 1) && !visited[neighbour - 1]) {
                dfs(neighbour, colony);
            }
        }
    }


    public void printColonies(List<Colony> discoveredColonies) {
        // Print the given list of discovered colonies conforming to the given output format.
        // TODO: Your code here
        System.out.println("Discovered colonies are: ");
        int counter = 1;
        for (Colony colony : discoveredColonies) {
            List<Integer> sortedCities = new ArrayList<>(colony.cities);
            Collections.sort(sortedCities);
            System.out.print("Colony " + counter + ": ");
            System.out.println(sortedCities);
            counter++;
        }

    }

}
