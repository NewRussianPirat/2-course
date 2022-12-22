public class Truck {
    private final String model;
    private final double capacity;
    private final String color;
    private final double weight;
    private final double cost;

    private Truck(Builder builder) {
        this.model = builder.model;
        this.capacity = builder.capacity;
        this.color = builder.color;
        this.weight = builder.weight;
        this.cost = builder.cost;
    }

    public String getModel() {
        return this.model;
    }

    public double getCapacity() {
        return this.capacity;
    }

    public String getColor() {
        return this.color;
    }

    public double getWeight() {
        return this.weight;
    }

    public double getCost() {
        return this.cost;
    }

    @Override
    public String toString() {
        return "model: " + this.model + ", capacity: " + this.capacity + ", color: "
                + this.color + ", weight: " + this.weight + ", cost: " + this.cost;
    }

    public static class Builder {
        private String model;
        private double capacity;
        private String color;
        private double weight;
        private double cost;

        public Builder setModel(String model) {
            this.model = model;
            return this;
        }

        public Builder setCapacity(double capacity) {
            this.capacity = capacity;
            return this;
        }

        public Builder setColor(String color) {
            this.color = color;
            return this;
        }

        public Builder setWeight(double weight) {
            this.weight = weight;
            return this;
        }

        public Builder setCost(double cost) {
            this.cost = cost;
            return this;
        }

        public Truck build() {
            return new Truck(this);
        }
    }
}
