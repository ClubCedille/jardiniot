#include "CommandManager.hpp"

#include <iostream>
#include <iterator>
#include <vector>


//<<constructor>>
CommandManager::CommandManager():
    factory(new ControllerFactory())
{
    
}

//<<destructor>>
CommandManager::~CommandManager(){
}

std::string CommandManager::executeCommand(std::string command){
    JardinCommand* jCommand = new JardinCommand(command);
    std::string msg = "";
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

short CommandManager::getSensor(SensorStrategy * sensor, unsigned char idController){
    int i = 0;
    auto it = this->sensorList.begin();
    while( it != this->sensorList.end() )
    {
        i++;
        auto ret = std::next(it);
        if((*it)->getIdController() == idController)
        {
            *sensor = *ret[i];
            return i;
        }
    }
    // Le senseur n'a pas été trouvé
    return -1;
}

short CommandManager::getActuator(ActuatorStrategy * motor, unsigned char idController){
    int i = 0;
    auto it = this->actuatorList.begin();
    while( it != this->actuatorList.end() )
    {
        i++;
        auto ret = std::next(it);
        if((*it)->getIdController() == idController)
        {
            *motor = *ret[i];
            return i;
        }
    }
    // Le senseur n'a pas été trouvé
    return -1;
}

std::string CommandManager::modifyController(JardinCommand &jCommand){
    std::string msg = jCommand.getError();
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
            SensorStrategy* sc = NULL;

            int index = this->getSensor(sc, idController);
            // return "INDEX :" + std::string(index);
            // Si le sensor est trouvé le modifier
            if(index != -1){
                // Modifier le senseur
                this->sensorList[index]->modify(jCommand);
            }
        }else if(Motor == controlType){
            ActuatorStrategy* mStrat = NULL;

            int index = this->getActuator(mStrat, idController);
            // Si le sensor est trouvé le modifier
            if(index != -1){
                // Modifier le senseur
                this->actuatorList[index]->modify(jCommand);
            }
        }
        else{
            // TODO
        }

    }


    return msg;
}

std::string CommandManager::removeController(JardinCommand &jCommand){
    std::string msg = jCommand.getError();
    if(msg.length() != 0){
        return msg;
    }

    int idController = jCommand.getIdController();

    // Aller chercher le type du controller passé dans la commande
    Type controlType = ControllerTypeValidator::getTypeFromController(jCommand.getControllerType());

    if(Sensor == controlType){
        SensorStrategy* sc = NULL;

        int index = this->getSensor(sc, idController);
        // Si le sensor est trouvé le supprimer
        if(index != -1){
            // Supprimer l'objet SensorStrategy
            delete this->sensorList[index];
            // Supprimer l'item de la liste
            this->sensorList.erase(this->sensorList.begin()+index);
        }
    }else if(Motor == controlType){
        ActuatorStrategy* mStrat = NULL;

        int index = this->getActuator(mStrat, idController);
        // Si le sensor est trouvé le supprimer
        if(index != -1){
            // Supprimer l'objet SensorStrategy
            delete this->actuatorList[index];
            // Supprimer l'item de la liste
            this->actuatorList.erase(this->actuatorList.begin()+index);
        }
    }
    else{
        // TODO
    }

    return msg;

}

std::string CommandManager::addController(JardinCommand &jCommand){
    std::string msg = jCommand.getError();
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
        ActuatorStrategy* motor = this->factory->createMotor(jCommand.getIdController(), jCommand.getControllerType(), jCommand.getDelay(), jCommand.getInputPin(), jCommand.getOutputPin());
        this->actuatorList.push_back(motor);
    }else if(Both == controlType){
        // TODO Si un jour a des senseurs qui sont aussi des moteurs
    }

    return msg;
}

bool CommandManager::isIdControllerUsed(unsigned char idController){

    for(unsigned int i = 0; i < this->sensorList.size(); i++){
        if(this->sensorList[i]->getIdController() == idController){
            return true;
        }
    }
    for(unsigned int i = 0; i < this->actuatorList.size(); i++){
        if(this->actuatorList[i]->getIdController() == idController){
            return true;
        }
    }
    return false;
}

std::vector<SensorStrategy*> CommandManager::getSensorList(){
    return this->sensorList;
}

std::vector<ActuatorStrategy*> CommandManager::getActuatorList(){
    return this->actuatorList;
}
