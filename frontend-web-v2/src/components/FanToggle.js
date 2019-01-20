import React from 'react';
import Switch from 'react-switch';


export default class FanToggle extends React.Component {
  constructor(props) {
    super(props);

    // set state..
    this.state = {
      ...props,
      checked: false
    } 
  }

  handleChange(checked) {
    this.setState({ checked });
  }

  render() {
    return (
      <div className="fan">
        <div className="name">{this.props.name}</div>
        <Switch
          onChange={this.handleChange.bind(this)}
          checked={this.state.checked}
          id="normal-switch"
          className="switch"
        />
      </div>
    )
  }
}