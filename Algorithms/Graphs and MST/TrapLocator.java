import java.util.*;

public class TrapLocator {
    public List<Colony> colonies;

    public TrapLocator(List<Colony> colonies) {
        this.colonies = colonies;
    }

    public List<List<Integer>> revealTraps() {

        // Trap positions for each colony, should contain an empty array if the colony is safe.
        // I.e.:
        // 0 -> [2, 15, 16, 31]
        // 1 -> [4, 13, 22]
        // 3 -> []
        // ...
        List<List<Integer>> traps = new ArrayList<>();

        // Identify the time traps and save them into the traps variable and then return it.
        // TODO: Your code here
        for(Colony colony : colonies){
            boolean hasCombination = false;
            Set<List<Integer>> visitedCombinations = new HashSet<>();
            for (Integer firstKey : colony.roadNetwork.keySet()) {
                List<Integer> firstValues = colony.roadNetwork.get(firstKey);
                for (Integer secondKey : firstValues) {
                    List<Integer> secondValues = colony.roadNetwork.get(secondKey);
                    for (Integer thirdKey : secondValues) {
                        List<Integer> thirdValues = colony.roadNetwork.get(thirdKey);
                        for (Integer fourthKey : thirdValues){
                            if(firstKey.equals(fourthKey)){
                                List<Integer> combination = Arrays.asList(firstKey, secondKey, thirdKey);
                                Collections.sort(combination);

                                if (!visitedCombinations.contains(combination)) {
                                    visitedCombinations.add(combination);
                                    hasCombination = true;
                                    traps.add(combination);

                                }

                            }
                        }
                    }
                }
            }
            if (!hasCombination) {
                traps.add(Collections.emptyList());

            }
        }

        return traps;
    }

    public void printTraps(List<List<Integer>> traps) {
        // For each colony, if you have encountered a time trap, then print the cities that create the trap.
        // If you have not encountered a time trap in this colony, then print "Safe".
        // Print the your findings conforming to the given output format.
        // TODO: Your code here
        int counter = 1;
        System.out.println("Danger exploration conclusions: ");
        for (List<Integer> trap : traps){
            if(trap.isEmpty()){
                System.out.println("Colony " + counter + ": Safe");
            }else{
                System.out.println("Colony " + counter + ": Dangerous. Cities on the dangerous path: " + trap);
            }
            counter++;
        }
    }

}
