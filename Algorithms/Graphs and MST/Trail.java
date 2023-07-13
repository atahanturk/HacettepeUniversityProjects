public class Trail {
    public Location source;
    public Location destination;
    public int danger;

    public Trail(Location source, Location destination, int danger) {
        this.source = source;
        this.destination = destination;
        this.danger = danger;
    }

    public int getDanger() {
        return danger;
    }

    public Location getSource() {
        return source;
    }

    public Location getDestination() {
        return destination;
    }

}
