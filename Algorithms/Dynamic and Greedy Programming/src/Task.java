import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class Task implements Comparable {
    public String name;
    public String start;
    public int duration;
    public int importance;
    public boolean urgent;


    /*
        Getter methods
     */
    public String getName() {
        return this.name;
    }

    public String getStartTime() {
        return this.start;
    }

    public int getDuration() {
        return this.duration;
    }

    public int getImportance() {
        return this.importance;
    }

    public boolean isUrgent() {
        return this.urgent;
    }

    /**
     * Finish time should be calculated here
     *
     * @return calculated finish time as String
     */
    public String getFinishTime() {
        // YOUR CODE HERE
        LocalTime start_time = LocalTime.parse(getStartTime(), DateTimeFormatter.ofPattern("HH:mm"));
        LocalTime finish_time = start_time.plusHours(getDuration());
        return finish_time.format(DateTimeFormatter.ofPattern("HH:mm"));
    }

    /**
     * Weight calculation should be performed here
     *
     * @return calculated weight
     */
    public double getWeight() {
        // YOUR CODE HERE
        double weight = (getImportance() * (isUrgent() ? 2000 : 1)) / getDuration();
        return weight;

    }

    /**
     * This method is needed to use {@link java.util.Arrays#sort(Object[])} ()}, which sorts the given array easily
     *
     * @param o Object to compare to
     * @return If self > object, return > 0 (e.g. 1)
     * If self == object, return 0
     * If self < object, return < 0 (e.g. -1)
     */
    @Override
    public int compareTo(Object o) {
        // YOUR CODE HERE
        Task comparing_tasks = (Task) o;
        LocalTime localTime1 = LocalTime.parse(this.getFinishTime());
        LocalTime localTime2 = LocalTime.parse(comparing_tasks.getFinishTime());

        if (localTime1.isAfter(localTime2)) {
            return 1;
        } else if (localTime1.isBefore(localTime2)) {
            return -1;
        } else {
            return 0;
        }



    }
}
