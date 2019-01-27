import React from 'react';
import Switch from 'react-switch';
import API from '../Api';


export default class FanToggle extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      ...props,
      checked: parseInt(props.fan.value) === 255
    }
  }

  handleChange = async (checked) => {
    this.setState({ checked });
    await this.props.handleChange(checked);
  }

  render() {
    return (
      <div className="fan">
        <div className="name">{this.state.fan.name}</div>
        <Switch
          onChange={this.handleChange}
          checked={this.state.checked}
          id="normal-switch"
          className="switch"
        />
      </div>
    )
  }
}