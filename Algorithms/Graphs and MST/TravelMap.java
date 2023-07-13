import jdk.swing.interop.SwingInterOpUtils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.*;

public class TravelMap {

    // Maps a single Id to a single Location.
    public Map<Integer, Location> locationMap = new HashMap<>();

    // List of locations, read in the given order
    public List<Location> locations = new ArrayList<>();

    // List of trails, read in the given order
    public List<Trail> trails = new ArrayList<>();

    // TODO: You are free to add more variables if necessary.

    public void initializeMap(String filename){
        // Read the XML file and fill the instance variables locationMap, locations and trails.
        // TODO: Your code here
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(filename);
            document.getDocumentElement().normalize();
            NodeList locationnodes = document.getElementsByTagName("Location");

            for (int i = 0; i < locationnodes.getLength(); i++) {
                Node locnode = locationnodes.item(i);

                if (locnode.getNodeType() == Node.ELEMENT_NODE) {
                    Element locelement = (Element) locnode;
                    String name = locelement.getElementsByTagName("Name").item(0).getTextContent();
                    int id = Integer.parseInt(locelement.getElementsByTagName("Id").item(0).getTextContent());
                    Location location = new Location(name, id);
                    locationMap.put(id, location);
                    locations.add(location);
                }
            }

            NodeList trailnodes = document.getElementsByTagName("Trail");

            for (int i = 0; i < trailnodes.getLength(); i++) {
                Node tranode = trailnodes.item(i);
                if (tranode.getNodeType() == Node.ELEMENT_NODE) {
                    Element traelement = (Element) tranode;
                    int sourceId = Integer.parseInt(traelement.getElementsByTagName("Source").item(0).getTextContent());
                    int dstId = Integer.parseInt(traelement.getElementsByTagName("Destination").item(0).getTextContent());
                    Location source = locationMap.get(sourceId);
                    Location destination = locationMap.get(dstId);
                    int danger = Integer.parseInt(traelement.getElementsByTagName("Danger").item(0).getTextContent());
                    Trail trail = new Trail(source, destination, danger);
                    trails.add(trail);

                }
            }
        }catch (ParserConfigurationException | SAXException | IOException e) {
            // Handle the exceptions here
            e.printStackTrace();
        }
    }



    public List<Trail> getSafestTrails() {
        List<Trail> safestTrails = new ArrayList<>();
        // Fill the safestTrail list and return it.
        // Select the optimal Trails from the Trail list that you have read.
        // TODO: Your code here

        PriorityQueue<Trail> pq = new PriorityQueue<>(Comparator.comparingInt(Trail::getDanger));
        pq.addAll(trails);

        int[] root = new int[locations.size()];
        for (int i=0; i<locations.size(); i++) {
            root[i] = i;
        }

        while (!pq.isEmpty()) {
            Trail edge = pq.poll();
            int sourceRoot = edge.getSource().getId();
            int dstRoot = edge.getDestination().getId();

            while (root[sourceRoot] != sourceRoot) {
                sourceRoot = root[sourceRoot];
            }

            while (root[dstRoot] != dstRoot) {
                dstRoot = root[dstRoot];
            }

            if (sourceRoot != dstRoot) {
                root[sourceRoot] = dstRoot;
                safestTrails.add(edge);
            }
        }

        return safestTrails;
    }


    public void printSafestTrails(List<Trail> safestTrails) {
        // Print the given list of safest trails conforming to the given output format.
        // TODO: Your code here
        int totalDanger = 0;
        System.out.println("Safest trails are:");
        for (Trail safestTrail : safestTrails) {
            System.out.println("The trail from " + safestTrail.getSource().getName() +
                    " to " + safestTrail.getDestination().getName() + " with danger " + safestTrail.getDanger());
            totalDanger += safestTrail.danger;

        }
        System.out.println("Total danger: " + totalDanger);
    }
}
