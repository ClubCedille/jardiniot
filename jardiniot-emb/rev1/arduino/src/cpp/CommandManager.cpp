#include "include/CommandManager.h"

//<<constructor>>
CommandManager::CommandManager(){
    this->factory = new ControllerFactory();
}

//<<destructor>>
CommandManager::~CommandManager(){
}

String CommandManager::executeCommand(String command){
    JardinCommand* jCommand = new JardinCommand(command);
    String msg = "";
    switch (jCommand->getCommandType()) {
        case ADD: msg = this->addController(*jCommand);
        break;
        case CONFIG: msg = this->modifyController(*jCommand);
        break;
        case DELETE: msg = this->removeController(*jCommand);
        break;
    }
    delete jCommand;
    return msg;
}

short CommandManager::getSensor(std::vector<SensorStrategy*>::iterator it, SensorStrategy *sensor, byte idController){
    int i = 0;
    for(it = this->sensorList.begin() ; it != this->sensorList.end(); ++it, i++){
        if((*it)->getIdController() == idController){
            sensor = *it;
            return i;
        }
    }
    // Le senseur n'a pas été trouvé
    return -1;
}

short CommandManager::getMotor(std::vector<MotorStrategy*>::iterator it, MotorStrategy *motor, byte idController){
    int i = 0;
    for(it = this->motorList.begin() ; it != this->motorList.end(); ++it, i++){
        if((*it)->getIdController() == idController){
            motor = *it;
            return i;
        }
    }
    // Le moteur n'a pas été trouvé
    return -1;
}

String CommandManager::modifyController(JardinCommand &jCommand){
    String msg = jCommand.getError();
    if(msg.length() != 0){
        return msg;
    }

    int idController = jCommand.getIdController();

    if(!this->isIdControllerUsed(idController)){
        return "Erreur le controller n'a jamais été créé";
    }
    else{
        // Aller chercher le type du controller passé dans la commande
        Type controlType = ControllerTypeValidator::getTypeFromController(jCommand.getControllerType());
        if(Sensor == controlType){
            std::vector<SensorStrategy*>::iterator it;
            SensorStrategy* sc;

            int index = this->getSensor(it, sc, idController);
            // return "INDEX :" + String(index);
            // Si le sensor est trouvé le modifier
            if(index != -1){
                // Modifier le senseur
                this->sensorList[index]->modify(jCommand);
            }
        }else if(Motor == controlType){
            std::vector<MotorStrategy*>::iterator it;
            MotorStrategy* mStrat;

            int index = this->getMotor(it, mStrat, idController);
            // Si le sensor est trouvé le modifier
            if(index != -1){
                // Modifier le senseur
                this->motorList[index]->modify(jCommand);
            }
        }
        else{
            // TODO
        }

    }


    return msg;
}

String CommandManager::removeController(JardinCommand &jCommand){
    String msg = jCommand.getError();
    if(msg.length() != 0){
        return msg;
    }

    int idController = jCommand.getIdController();

    // Aller chercher le type du controller passé dans la commande
    Type controlType = ControllerTypeValidator::getTypeFromController(jCommand.getControllerType());

    if(Sensor == controlType){
        std::vector<SensorStrategy*>::iterator it;
        SensorStrategy* sc;

        int index = this->getSensor(it, sc, idController);
        // Si le sensor est trouvé le supprimer
        if(index != -1){
            // Supprimer l'objet SensorStrategy
            delete this->sensorList[index];
            it = this->sensorList.begin();
            // Supprimer l'item de la liste
            this->sensorList.erase(it+index);
        }
    }else if(Motor == controlType){
        std::vector<MotorStrategy*>::iterator it;
        MotorStrategy* mStrat;

        int index = this->getMotor(it, mStrat, idController);
        // Si le sensor est trouvé le supprimer
        if(index != -1){
            // Supprimer l'objet SensorStrategy
            delete this->motorList[index];
            it = this->motorList.begin();
            // Supprimer l'item de la liste
            this->motorList.erase(it+index);
        }
    }
    else{
        // TODO
    }

    return msg;

}

String CommandManager::addController(JardinCommand &jCommand){
    String msg = jCommand.getError();
    if(msg.length() != 0){
        return msg;
    }
    // Aller chercher le type du controller passé dans la commande
    Type controlType = ControllerTypeValidator::getTypeFromController(jCommand.getControllerType());

    if(this->isIdControllerUsed(jCommand.getIdController())){
        return "Erreur le idController est déjà utilisé";
    }

    // Si aucune erreur on peut créer le controller
    if(Sensor == controlType){
        SensorStrategy* sensor = this->factory->createSensor(jCommand.getIdController(), jCommand.getControllerType(), jCommand.getDelay(), jCommand.getInputPin(), jCommand.getOutputPin());
        this->sensorList.push_back(sensor);
    }else if(Motor == controlType){
        // Fait la création des fonctions pour les moteurs
        MotorStrategy* motor = this->factory->createMotor(jCommand.getIdController(), jCommand.getControllerType(), jCommand.getDelay(), jCommand.getInputPin(), jCommand.getOutputPin());
        this->motorList.push_back(motor);
    }else if(Both == controlType){
        // TODO Si un jour a des senseurs qui sont aussi des moteurs
    }

    return msg;
}

bool CommandManager::isIdControllerUsed(byte idController){

    for(unsigned int i = 0; i < this->sensorList.size(); i++){
        if(this->sensorList[i]->getIdController() == idController){
            return true;
        }
    }
    for(unsigned int i = 0; i < this->motorList.size(); i++){
        if(this->motorList[i]->getIdController() == idController){
            return true;
        }
    }
    return false;
}

std::vector<SensorStrategy*> CommandManager::getSensorList(){
    return this->sensorList;
}

std::vector<MotorStrategy*> CommandManager::getMotorList(){
    return this->motorList;
}
