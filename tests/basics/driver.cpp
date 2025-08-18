#include <OpenSim/OpenSim.h>

#include <iostream>

using namespace std;
using namespace SimTK;
using namespace OpenSim;

int main()
{
    Logger::removeFileSink(); // Don't create opensim.log

    cout << "start hello world" << endl;
    Model model;
    model.setName("bicep_curl");
    model.setUseVisualizer(true);

    cout << "start hello world2" << endl;

    // Create two links, each with a mass of 1 kg, center of mass at the body's
    // origin, and moments and products of inertia of zero.
    OpenSim::Body* humerus = new OpenSim::Body("humerus", 1, Vec3(0), Inertia(0));
    OpenSim::Body* radius  = new OpenSim::Body("radius",  1, Vec3(0), Inertia(0));

    // Connect the bodies with pin joints. Assume each body is 1 m long.
    PinJoint* shoulder = new PinJoint("shoulder",
            // Parent body, location in parent, orientation in parent.
            model.getGround(), Vec3(0), Vec3(0),
            // Child body, location in child, orientation in child.
            *humerus, Vec3(0, 1, 0), Vec3(0));
    PinJoint* elbow = new PinJoint("elbow",
            *humerus, Vec3(0), Vec3(0), *radius, Vec3(0, 1, 0), Vec3(0));


    cout << "start hello world3" << endl;
    // Add a muscle that flexes the elbow.
    Millard2012EquilibriumMuscle* biceps = new
        Millard2012EquilibriumMuscle("biceps", 200, 0.6, 0.55, 0);
    biceps->addNewPathPoint("origin",    *humerus, Vec3(0, 0.8, 0));
    biceps->addNewPathPoint("insertion", *radius,  Vec3(0, 0.7, 0));

    // Add a controller that specifies the excitation of the muscle.
    PrescribedController* brain = new PrescribedController();
    brain->addActuator(*biceps);
    // Muscle excitation is 0.3 for the first 0.5 seconds, then increases to
    // 1.
    StepFunction sf{0.5, 3, 0.3, 1};
    brain->prescribeControlForActuator(string("biceps"), sf);

    cout << "start hello world4" << endl;
    // Add components to the model.
    model.addBody(humerus);    model.addBody(radius);
    model.addJoint(shoulder);  model.addJoint(elbow);
    model.addForce(biceps);
    model.addController(brain);

    cout << "start hello world5" << endl;
    // Add a console reporter to print the muscle fiber force and elbow angle.
    ConsoleReporter* reporter = new ConsoleReporter();
    reporter->set_report_time_interval(1.0);
    reporter->addToReport(biceps->getOutput("fiber_force"));
    reporter->addToReport(
        elbow->getCoordinate(PinJoint::Coord::RotationZ).getOutput("value"),
        "elbow_angle");
    model.addComponent(reporter);

    cout << "start hello world6" << endl;
    // Add display geometry.
    Ellipsoid bodyGeometry(0.1, 0.5, 0.1);
    bodyGeometry.setColor(Gray);
    // Attach an ellipsoid to a frame located at the center of each body.
    PhysicalOffsetFrame* humerusCenter = new PhysicalOffsetFrame(
        "humerusCenter", *humerus, Transform(Vec3(0, 0.5, 0)));
    humerus->addComponent(humerusCenter);
    humerusCenter->attachGeometry(bodyGeometry.clone());
    PhysicalOffsetFrame* radiusCenter = new PhysicalOffsetFrame(
        "radiusCenter", *radius, Transform(Vec3(0, 0.5, 0)));
    radius->addComponent(radiusCenter);
    radiusCenter->attachGeometry(bodyGeometry.clone());

    cout << "start hello world7" << endl;
    // Configure the model.
    model.setUseVisualizer(false);
    State& state = model.initSystem();
    cout << "start hello world7.5" << endl;
    // Fix the shoulder at its default angle and begin with the elbow flexed.
    shoulder->getCoordinate().setLocked(state, true);
    cout << "start hello world7.6" << endl;
    elbow->getCoordinate().setValue(state, 0.5 * Pi);
    cout << "start hello world7.7" << endl;
    model.equilibrateMuscles(state);


    cout << "start hello world8" << endl;
    // Configure the visualizer.
    model.updMatterSubsystem().setShowDefaultGeometry(true);

    cout << "start hello world9" << endl;
    // Simulate.
    simulate(model, state, 10.0);

    cout << "hello world" << endl;
    return 0;
}
