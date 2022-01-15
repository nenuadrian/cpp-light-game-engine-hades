#include "physics.h"


void Physics::Render() {
	if (eventManager->play && !eventManager->breakRender) {
		Physics::SetupEntities();

		dynamicsWorld->stepSimulation(1.f / 60.f, 10);
		
		auto view = manager->registry.view<RigidBody, Thing*>();
		for (auto [entity, body, thing] : view.each()) {
			btCollisionObject* obj = body.btCollisionObject;
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
			else
			{
				trans = obj->getWorldTransform();
			}
			printf("world pos object %f,%f,%f\n", float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
			thing->x += trans.getOrigin().getX();
			thing->y += trans.getOrigin().getY();
			thing->z += trans.getOrigin().getZ();
		}
	}
}


void Physics::Setup() {
	if (eventManager->play) {
		initialized = true;

		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		collisionConfiguration = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		dispatcher = new btCollisionDispatcher(collisionConfiguration);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		overlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		solver = new btSequentialImpulseConstraintSolver;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));
	}
}

void Physics::SetupEntities() {
	btCollisionShape* groundShape;
	groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
	collisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -56, 0));

	btScalar mass(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	auto view = manager->registry.view<RigidBody, Thing*>();
	for (auto [entity, body, things] : view.each()) {
		if (body.btCollisionObject == nullptr) {
			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
			btRigidBody* bodyR = new btRigidBody(rbInfo);
			body.btCollisionObject = bodyR;
			dynamicsWorld->addRigidBody(bodyR);
		}
	}
}

Physics::~Physics() {
	if (initialized) {
		//remove the rigidbodies from the dynamics world and delete them
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}

		//delete collision shapes
		for (int j = 0; j < collisionShapes.size(); j++)
		{
			btCollisionShape* shape = collisionShapes[j];
			collisionShapes[j] = 0;
			delete shape;
		}

		//delete dynamics world
		delete dynamicsWorld;

		//delete solver
		delete solver;

		//delete broadphase
		delete overlappingPairCache;

		//delete dispatcher
		delete dispatcher;

		delete collisionConfiguration;

		//next line is optional: it will be cleared by the destructor when the array goes out of scope
		collisionShapes.clear();
	}
}